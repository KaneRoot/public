<?php

/* pas secure */
function getCompagnie()
{
	if(! isset($conn))
		include('co.php');

	$login = $_SESSION['login'];

	$query = "select idCompagnie 
	from GESTIONNAIRE
	where UPPER(loginGestionnaire) = UPPER(:login)";

	$stmt = oci_parse($conn, $query);
	oci_bind_by_name($stmt, ':login', $login);
	if( ! oci_execute($stmt))
		die("Il y a eu une erreur dans la recherche de la compagnie du gestionnaire.");

	if( ! ( $row = oci_fetch_assoc($stmt)))
		die("Il y a eu une erreur dans la recherche de la compagnie du gestionnaire $login.");

	$compagnie = $row['IDCOMPAGNIE'];

	return $compagnie;
}
function estGestionnaire()
{
	return ! (! isset($_SESSION['connexion'], $_SESSION['login']) || 
			strcmp($_SESSION['connexion'] , "gestionnaire") != 0 );
}
function verifier_est_gestionnaire()
{
	if(! estGestionnaire())
	{
		header("Location: connexionAdmin.php");
	}
}
function modifierVol( $idvol, $compagnie , $conn)
{
	if(isset($_POST['villedepart'], $_POST['villearrivee'], 
				$_POST['datedepart'], $_POST['datearrivee']))
	{
		$villedepart = $_POST['villedepart'];
		$villearrivee = $_POST['villearrivee'];
		$datedepart = "to_date( '". $_POST['datedepart'] . "' ,'yyyy/mm/dd hh24:mi:ss' )";
		$datearrivee = "to_date( '". $_POST['datearrivee'] . "' ,'yyyy/mm/dd hh24:mi:ss' )";

		$query = "update VOL set idVilleDepart=$villedepart ,
			idVilleArrivee=$villearrivee ,
			dateDepart=$datedepart ,
			dateArrivee=$datearrivee 
			where idVol=$idvol and idCompagnie=$compagnie";
		
		$stmt = oci_parse($conn, $query);
		if(! oci_execute($stmt))
			die("Erreur à l'update de la table. <br /> $query");
	}
}
function ajout_billet($idvol, $compagnie, $conn)
{
	if(isset($_POST['prix']))
	{
		$prix = $_POST['prix'];
		$promo = '0';

		if(isset($_POST['promotion']) && strlen($_POST['promotion']) > 0)
			$promo = $_POST['promotion'];

		$query =
		"insert into BILLET VALUES(seq_billet.nextVal, :idvol, :compagnie,
			:prix, :promo, NULL)";
		
		$stmt = oci_parse($conn, $query);
		oci_bind_by_name($stmt, ':idvol', $idvol);
		oci_bind_by_name($stmt, ':compagnie', $compagnie);
		oci_bind_by_name($stmt, ':prix', $prix);
		oci_bind_by_name($stmt, ':promo', $promo);

		if(! oci_execute($stmt))
			die("Erreur à l'update de la table. <br /> $query");
	}
}
function get_prochain_idvol($conn)
{
	$compagnie = getCompagnie();
	$query = "select max(idVol)+1 as prochainid from VOL where idCompagnie=:compagnie";

	$stmt = oci_parse($conn, $query);
	oci_bind_by_name($stmt, ':compagnie', $compagnie);

	if(! oci_execute($stmt))
		die("Erreur à l'update de la table. <br /> $query");
	$row = oci_fetch_assoc($stmt);

	return $row['PROCHAINID'];
}
function afficher_les_vols($conn)
{
	affichage_vols('', '',$conn);
}
function affichage_vols($vdepart, $varrivee, $conn)
{
	supprimer_vol($conn);

	if(isset($_GET['classement']))
	{
		$classement = "ORDER BY ";
		if(strcmp($_GET['classement'], "duree" ) == 0)
			$classement .= "dureeh ASC, dureem ASC";
		else if(strcmp($_GET['classement'], "nb_escales") == 0)
			$classement .= "escales ASC";
		else if(strcmp($_GET['classement'], "date_de_depart") == 0)
			$classement .= "datedepart ASC";
		else if(strcmp($_GET['classement'], "prix") == 0)
			$classement .= "prix ASC";
		else if(strcmp($_GET['classement'], "compagnie") == 0)
			$classement .= "C.idCompagnie ASC";
	}
	if(estGestionnaire())
		$compagnie = getCompagnie();

	/* requête un peu complexe */
	$query = 
	"select 
		V.idVol as idvol, 
		C.nomCompagnie as compagnie, 
		C.idCompagnie as idcompagnie,
		X.nomVille as vdepart, Y.nomVille as varrivee, 
		to_char(V.dateDepart, 'yyyy/mm/dd hh24:mi:ss') as datedepart, 
		to_char(V.dateArrivee, 'yyyy/mm/dd hh24:mi:ss') as datearrivee,
		trunc((V.dateArrivee - V.dateDepart)*24) as dureeh,
		trunc( MOD(( (V.dateArrivee - V.dateDepart)*24*60),60)) as dureem,
		V.idCompagnie as idcompagnie,
		nb_billets_reserve(V.idVol, V.idCompagnie) as billetsreserves,
		nb_billets_achetes(V.idVol, V.idCompagnie) as billetsachetes,
		nb_billets_restants(V.idVol, V.idCompagnie) as billetsrestants,
		nb_escales(V.idVol, V.idCompagnie) as escales,
		prixmin(V.idVol, V.idCompagnie) as prix
	from VOL V 
	JOIN COMPAGNIE C ON V.idCompagnie=C.idCompagnie
	JOIN VILLE X ON X.idVille=V.idVilleDepart
	JOIN VILLE Y ON Y.idVille=V.idVilleArrivee
	where V.dateDepart > SYSDATE 
	";

	if(strlen($vdepart) > 0)
		$query .= " and V.idVilleDepart=$vdepart";
	if(strlen($varrivee) > 0)
		$query .= " and V.idVilleArrivee=$varrivee";

	if(isset($compagnie))
		$query .= " and V.idCompagnie=$compagnie ";
	else
		$query .= " and nb_billets_restants(V.idVol, V.idCompagnie) > 0 ";

	if(isset($classement))
		$query .= $classement;

	$stmt = oci_parse($conn, $query);
	if(! oci_execute($stmt))
		die("Il y a eu une erreur lors de la recherche des vols. ");

	?>
		<table>
			<thead>
				<tr>
					<th>id</th>
					<th><a href='?classement=compagnie' >Compagnie</a></th>
					<th>Ville de départ</th>
					<th>Ville d'arrivée</th>
					<th><a href="?classement=date_de_depart" >Date de départ</a></th>
					<th>Date d'arrivée</th>
					<th><a href="?classement=duree">Durée</a></th>
					<th>Billets réservés</th>
					<th>Billets achetés</th>
					<th>Billets restants</th>
					<th><a href="?classement=prix" >Prix</a></th>
					<th><a href="?classement=nb_escales" >Nb d'escales</a></th>
<?php 
					
if(estGestionnaire()) 
{ 
	echo "<th>Suppr</th>"; 
} 
else
{
	echo "<th>Voir billets</th>";
}
?>
				</tr>
			</thead>

<?php
while($row = oci_fetch_assoc($stmt))
{
	echo "<tr>";
	$vol = $row['IDVOL'];
	$compagnie = $row['IDCOMPAGNIE'];

	if(estGestionnaire())
	{
		echo "<td><a href='modifier_vols.php?idvol=$vol'. >$vol</a></td>";
	}
	else
	{
		echo "<td>$vol</td>";
	}
	echo 
		"<td>" . $row['COMPAGNIE'] . " </td> " .
		"<td>" . $row['VDEPART'] . " </td> " .
		"<td>" . $row['VARRIVEE'] . " </td> " .
		"<td>" . $row['DATEDEPART'] . " </td> " .
		"<td>" . $row['DATEARRIVEE'] . " </td> " . 
		"<td>" . $row['DUREEH'] .":". $row['DUREEM'] . " </td> " . 
		"<td>" . $row['BILLETSRESERVES'] . " </td> " . 
		"<td>" . $row['BILLETSACHETES'] . " </td> " .
		"<td>" . $row['BILLETSRESTANTS'] . "</td>" .
		"<td>" . $row['PRIX'] . "</td>" .
		"<td>" . $row['ESCALES'] . "</td>";

if(estGestionnaire()) 
{ 
	echo "<td><a href='?supprimer_vol=$vol' >
		<label class='blue radius label' >DELETE ME</label>
		</a></td>"; 
}
else
{
	echo "<td><a href='voir_billets.php?idvol=$vol&idcompagnie=$compagnie' >Voir billets</a></td>";
}

	echo "</tr>\n";
}

?>
		</table>
	<?php
}
function supprimer_vol($conn)
{
	if(! isset($_GET['supprimer_vol']))
		return false;

	$idvol_to_delete = $_GET['supprimer_vol'];
	$compagnie = getCompagnie();

	$query = "delete from VOL where idVol=:idvoltodelete and idCompagnie=:idCompagnie";
	$stmt = oci_parse($conn, $query);
	oci_bind_by_name($stmt, ':idvoltodelete', $idvol_to_delete);
	oci_bind_by_name($stmt, ':idCompagnie', $compagnie);

	if(! oci_execute($stmt))
		die("Erreur à la récupération des billets.");

	echo '<div class="alert-box success">';
	echo "Vol numéro $idvol_to_delete supprimé de la compagnie $compagnie.";
	echo '<a href="" class="close">&times;</a>';
	echo '</div>';

}
function afficher_billets($idvol, $compagnie, $conn)
{
	?>
		<!-- Début de la fonction d'affichage des billets -->
				<table>
					<thead>
						<th>id</th>
						<th>Prix</th>
						<th>Promo</th>
						<th>Prix HT</th>
						<?php
						if(estGestionnaire())
						{
							echo "<th>ÉTAT</th>
								<th>Supprimer</th>";
						}
						else
						{
							echo "<th>Réserver</th> <th> Acheter </th>";
						}
						?>
					</thead>

<?php
$query = 
"select B.idBillet as idBillet, B.prix as prix, B.promo as promo,
B.prix - B.promo as prixht, B.etatBillet as etat
from BILLET B
where B.idVol=:idvol and B.idCompagnie=:compagnie ";
if(! estGestionnaire())
	$query .= ' and B.etatBillet is null';

$query .= " ORDER BY prixht ASC";
$stmt = oci_parse($conn, $query);
oci_bind_by_name($stmt, ':idvol', $idvol);
oci_bind_by_name($stmt, ':compagnie', $compagnie);

if(! oci_execute($stmt))
	die("Erreur à la récupération des billets.");

while($row = oci_fetch_assoc($stmt))
{
	$idbillet = $row['IDBILLET'];
	echo '<tr>';
		echo 
			"<td>$idbillet</td>" .
			'<td>' . $row['PRIX'] . '</td>' .
			'<td>' . $row['PROMO'] . '</td>' .
			'<td>' . $row['PRIXHT'] . '</td>';

		if(estGestionnaire())
		{
			echo "<td>" . $row['ETAT'] . "</td>";
			echo "<td><a href='?suppression_billet=$idbillet&idvol=$idvol' >
				<label class='blue radius label' >DELETE ME</label>
				</a></td>";
		}
		else
		{
			?>
		<div id="reserverModal<?php echo $idbillet; ?>" class="reveal-modal">
			<h2>Reserver le billet <?php echo $idbillet; ?> ?</h2>
			<p class="lead">Oui hein ? Il est vraiment bien ce billet.</p>
			<a class="close-reveal-modal">&#215;</a>
			<?php echo "<a href='?reserverbillet=$idbillet&idvol=$idvol&idcompagnie=$compagnie' class='nice radius button' >Réserver !</a>"; ?>
		</div>
		<div id="acheterModal<?php echo $idbillet; ?>" class="reveal-modal">
			<h2>Acheter le billet <?php echo $idbillet; ?> ?</h2>
			<p class="lead">Oui hein ? Il est vraiment bien ce billet.</p>
			<a class="close-reveal-modal">&#215;</a>
			<?php echo "<a href='?acheterbillet=$idbillet&idvol=$idvol&idcompagnie=$compagnie' class='nice radius button' >Acheter !</a>"; ?>
		</div>
			<?php
			echo "	
			<td>
			<a data-reveal-id='reserverModal$idbillet' href='#' >
				<label class='blue radius label' >RESERVER</label>
			</a>
			</td>
			<td>
			<a data-reveal-id='acheterModal$idbillet' href='#' >
				<label class='blue radius label' >ACHETER</label>
			</a>
			</td>";
		}
	echo "</tr>\n";
}

?>
				</table>
	<?php
}
function annuler_reservation($conn)
{
	if(! isset($_GET['annulerreservation'], $_SESSION['idclient']))
		return false;

	$idclient = $_SESSION['idclient'];
	$idbillet = $_GET['annulerreservation'];

	$query = "begin annuler_reservation(:client, :idbillet); end;";

	$stmt = oci_parse($conn, $query );
	oci_bind_by_name($stmt, ':client', $idclient);
	oci_bind_by_name($stmt, ':idbillet', $idbillet);

	if(! oci_execute($stmt))
		die("Erreur à l'annulation de la réservation.");

	echo '<div class="alert-box success">';
	echo "Annulation de la réservation du billet : $idbillet ."; 
	echo '<a href="" class="close">&times;</a>';
	echo "</div>";

}
function achat_billet($conn)
{
	if(! isset($_GET['acheterbillet']))
		return false;

	if(! isset($_SESSION['idclient']))
		return false;

	$idclient = $_SESSION['idclient'];
	$idbillet = $_GET['acheterbillet'];

	$query = 'begin achat(:p1, :p2); end;';
	$stmt = oci_parse($conn, $query );
	oci_bind_by_name($stmt, ':p1', $idclient);
	oci_bind_by_name($stmt, ':p2', $idbillet);
	if(! oci_execute($stmt))
		die("Erreur à l'achat du billet.");

	echo '<div class="alert-box success">';
	echo "Billet acheté : $idbillet ."; 
	echo '<a href="" class="close">&times;</a>';
	echo "</div>";

}
function reservation_billet($idvol, $compagnie, $conn)
{
	if(! isset($_GET['reserverbillet']))
		return false;

	if(! isset($_SESSION['idclient']))
		return false;

	$idclient = $_SESSION['idclient'];
	$idbillet = $_GET['reserverbillet'];

	$query = 'begin reserver(:p1, :p2); end;';
	$stmt = oci_parse($conn, $query );
	oci_bind_by_name($stmt, ':p1', $idclient);
	oci_bind_by_name($stmt, ':p2', $idbillet);
	if(! oci_execute($stmt))
		die("Erreur à la réservation du billet.");

	echo '<div class="alert-box success">';
	echo "Billet réservé : $idbillet ."; 
	echo '<a href="" class="close">&times;</a>';
	echo "</div>";

}
function suppression_billet($idvol, $compagnie, $conn)
{
	if( ! isset($_GET['idvol'], $_GET['suppression_billet']))
		return false;

	$idvol = $_GET['idvol'];
	$idbillet = $_GET['suppression_billet'];

	$query = "delete from BILLET where idBillet=$idbillet";
	$stmt = oci_parse($conn, $query);
	if(! oci_execute($stmt))
		die("Erreur à la récupération des billets.");

	?>
	<div class="alert-box error">
	<?php echo "billet supprimé : $idbillet du vol $idvol de la compagnie $compagnie."; ?>
		<a href="" class="close">&times;</a>
	</div>
	<?php

}

function afficher_escales($idvol, $compagnie, $conn)
{

	$query = "select E.idescale as idescale, V.nomVille as nomville 
		from VILLE V JOIN ESCALE E ON E.idVille = V.idVille
		where E.idVol=$idvol and E.idCompagnie=$compagnie";

	$stmt = oci_parse($conn, $query);
	if(! oci_execute($stmt))
		die("Erreur à la récupération des info sur les escales.");
	
	$options = "";
	while($row = oci_fetch_assoc($stmt))
	{
		$idescale = $row['IDESCALE'];
		$nomville= $row['NOMVILLE'];
		$options .= "<tr><td>$idescale</td><td>$nomville</td>";
		if(estGestionnaire())
			$options .= "<td><a href='?supprimer_escale=$idescale&idvol=$idvol' >
				<label class='blue radius label' >DELETE ME</label>
				</a></td>";
		$options .= "</tr>\n";
	}
	?>
		<table>
			<thead>
				<th>id escale</th>
				<th>ville</th>
				<?php if(estGestionnaire()) { echo "<th>Supprimer</th>"; } ?>
			</thead>
	<?php
		echo $options;
	?>

		</table>
	<?php
}
function ajout_escale($idvol, $compagnie, $conn)
{
	if(! isset($_POST['escale_a_ajouter']))
		return false;
	$v = $_POST['escale_a_ajouter'];
	$query = "insert into ESCALE VALUES(seq_escale.nextVal, :idescale, :idvol, :compagnie)";
	$stmt = oci_parse($conn, $query);
	oci_bind_by_name($stmt, ':idescale', $v);
	oci_bind_by_name($stmt, ':idvol', $idvol);
	oci_bind_by_name($stmt, ':compagnie', $compagnie);

	if(! oci_execute($stmt))
		die("Erreur à l'insertion d'une nouvelle escale.");
	?>
	<div class="alert-box success">
	<?php echo "Ajout d'une escale au vol $idvol de la compagnie $compagnie."; ?>
		<a href="" class="close">&times;</a>
	</div>
	<?php

}
function suppression_escale($idvol, $compagnie, $conn)
{
	if(! isset($_GET['supprimer_escale']))
		return false;

	$escale = $_GET['supprimer_escale'];
	$query = "delete from ESCALE where idEscale=$escale";
	$stmt = oci_parse($conn, $query);
	if(! oci_execute($stmt))
		die("Erreur à la suppression de l'escale.");

	?>
	<div class="alert-box error">
	<?php echo "Suppression de l'escale $escale."; ?>
		<a href="" class="close">&times;</a>
	</div>
	<?php

}
function afficher_ajout_escale($idvol, $compagnie, $conn)
{
	$query = "select idVille, nomVille from VILLE where idVille not in
		(select idVille from ESCALE where idVol=$idvol and idCompagnie=$compagnie)";

	$stmt = oci_parse($conn, $query);
	if(! oci_execute($stmt))
		die("Erreur à la récupération des info sur les escales.");
	
	$options = "";
	while($row = oci_fetch_assoc($stmt))
	{
		$idville = $row['IDVILLE'];
		$nomville= $row['NOMVILLE'];
		$options .= "<option value=$idville >$nomville</option>\n";
	}

	?>
	<form class="nice" action="?idvol=<?php echo $idvol; ?>" method="POST" >
		<label for='escale_a_ajouter' class="blue radius label" >Escale à ajouter</label><br />
		<select id="escale_a_ajouter" name="escale_a_ajouter">
		<?php echo $options; ?>
		</select>

		<input type="submit" value="Ajouter cette escale à ce vol" />
	</form>
	<?php
}
function afficher_reservations($conn)
{

	if(! isset($_SESSION['idclient']))
		return false;

	$idclient = $_SESSION['idclient'];

	$query = "select 
		R.idBillet as idbillet
		from RESERVATION R JOIN BILLET B ON B.idBillet = R.idBillet
		JOIN VOL V ON V.idVol = B.idVol and V.idCompagnie = B.idCompagnie
		where ((V.dateDepart-SYSDATE)*24 <= 73 or (R.dateReservation - SYSDATE)* 24 >= 47) and R.idClient = :client";

	$stmt = oci_parse($conn, $query);
	oci_bind_by_name($stmt, ':client', $idclient);
	if(! oci_execute($stmt))
		die("Erreur à la récupération des info sur les réservations.");

	while($row = oci_fetch_assoc($stmt))
	{
		echo '<div class="alert-box error">';
		echo 'Attention, réservation ' . $row['IDBILLET'] . " expire dans moins d'une heure !";
		echo '<a href="" class="close">&times;</a>';
		echo '</div>';
	}

	/* Autre partie */
	$query = "select R.idBillet as idbillet, 
		to_char(R.dateReservation, 'yyyy/mm/dd hh24:mi:ss') as datereservation,
		B.prix as prix,
		B.promo as promo,
		V.idvol as vol,
		T.nomVille as villedepart,
		X.nomVille as villearrivee
		from RESERVATION R JOIN BILLET B ON B.idBillet = R.idBillet
		JOIN VOL V ON V.idVol = B.idVol and V.idCompagnie = B.idCompagnie
		JOIN VILLE T ON T.idVille = V.idVilleDepart
		JOIN VILLE X ON X.idVille = V.idVilleArrivee
		where idClient=:client";
	
	$stmt = oci_parse($conn, $query);
	oci_bind_by_name($stmt, ':client', $idclient);
	if(! oci_execute($stmt))
		die("Erreur à la récupération des info sur les réservations.");

	/* On affiche un message si on a réservé il y a plus de 47h ou si le départ est dans 73h */
	?>

		<table>
			<thead>
				<th>idBillet</th>
				<th>prix</th>
				<th>promo</th>
				<th>prix HT</th>
				<th>Ville de départ</th>
				<th>Ville d'arrivée</th>
				<th>N° Vol</th>
				<th>date de réservation</th>
				<th>Annuler</th>
				<th>Acheter</th>
			</thead>
		<?php
	while($row = oci_fetch_assoc($stmt))
	{
		$idbillet = $row['IDBILLET'];
		$date = $row['DATERESERVATION'];
		$prix = $row['PRIX'];
		$promo = $row['PROMO'];
		$villedepart = $row['VILLEDEPART'];
		$villearrivee = $row['VILLEARRIVEE'];
		$idvol = $row['VOL'];

		echo "<tr>\n";
		echo "
			<td>$idbillet</td>
			<td>$prix</td>
			<td>$promo</td>
			<td>" . ($prix - $promo) . "</td>
			<td>$villedepart</td>
			<td>$villearrivee</td>
			<td>$idvol</td>
			<td>$date</td>";
			?>
		<div id="annulerModal<?php echo $idbillet; ?>" class="reveal-modal">
			<h2>Annuler la réservation <?php echo $idbillet; ?> ?</h2>
			<p class="lead">Vous êtes sûr ?</p>
			<a class="close-reveal-modal">&#215;</a>
			<?php echo "<a href='?annulerreservation=$idbillet' class='nice radius button' >Annuler !</a>"; ?>
		</div>
		<div id="acheterModal<?php echo $idbillet; ?>" class="reveal-modal">
			<h2>Acheter le billet <?php echo $idbillet; ?> ?</h2>
			<p class="lead">Oui hein ? Il est vraiment bien ce billet.</p>
			<a class="close-reveal-modal">&#215;</a>
			<?php echo "<a href='?acheterbillet=$idbillet' class='nice radius button' >Acheter !</a>"; ?>
		</div>
		<?php
		echo "
			<td><a data-reveal-id='annulerModal$idbillet' href='#' >
				<label class='blue radius label' >Annuler</label>
			</a></td>
			<td><a data-reveal-id='acheterModal$idbillet' href='#' >
				<label class='blue radius label' >ACHETER</label>
			</a></td>";

		echo	"\n</tr>\n";

	}
	echo "</table>\n";

}

function afficher_achats($conn)
{
	if(! isset($_SESSION['idclient']))
		return false;

	$idclient = $_SESSION['idclient'];

	$query = "select A.idBillet as idbillet, 
		to_char(A.dateAchat, 'yyyy/mm/dd hh24:mi:ss') as dateachat,
		to_char(A.dateAchat, 'hh24') as heureachat,
		to_char(V.dateDepart, 'yyyy/mm/dd hh24:mi:ss') as datedepart,
		to_char(V.dateArrivee, 'yyyy/mm/dd hh24:mi:ss') as datearrivee,
		B.prix as prix,
		B.promo as promo,
		V.idvol as vol,
		T.nomVille as villedepart,
		X.nomVille as villearrivee
		from BILLET_CLIENT A JOIN BILLET B ON B.idBillet = A.idBillet
		JOIN VOL V ON V.idVol = B.idVol and V.idCompagnie = B.idCompagnie
		JOIN VILLE T ON T.idVille = V.idVilleDepart
		JOIN VILLE X ON X.idVille = V.idVilleArrivee
		where A.idClient=:idclient";
	
	$stmt = oci_parse($conn, $query);
	oci_bind_by_name($stmt, ':idclient', $idclient);
	if(! oci_execute($stmt))
		die("Erreur à la récupération des info sur les réservations.");

	?>

		<table>
			<thead>
				<th>idBillet</th>
				<th>N° Vol</th>
				<th>prix</th>
				<th>promo</th>
				<th>Ville de départ</th>
				<th>Ville d'arrivée</th>
				<th>Date de départ</th>
				<th>Date d'arrivée</th>
				<th>date d'achat</th>
				<th>prix final</th>
			</thead>
		<?php

	while($row = oci_fetch_assoc($stmt))
	{
		$idbillet = $row['IDBILLET'];
		$dateachat = $row['DATEACHAT'];
		$datedepart = $row['DATEDEPART'];
		$datearrivee = $row['DATEARRIVEE'];
		$prix = $row['PRIX'];
		$promo = $row['PROMO'];
		$villedepart = $row['VILLEDEPART'];
		$villearrivee = $row['VILLEARRIVEE'];
		$idvol = $row['VOL'];
		$heureachat = $row['HEUREACHAT']; 

		$prixtotal = $prix - $promo;

		if($heureachat >= 2 && $heureachat < 6)
			$prixtotal += 5;
		else if( $heureachat >= 6 && $heureachat < 22)
			$prixtotal += 20;
		else
			$prixtotal += 12;

		echo "<tr>\n";

		echo "
			<td>$idbillet </td>
			<td>$idvol </td>
			<td>$prix </td>
			<td>$promo </td>
			<td>$villedepart </td>
			<td>$villearrivee </td>
			<td>$datedepart </td>
			<td>$datearrivee </td>
			<td>$dateachat </td>
			<td>$prixtotal</td>
			";

		echo	"\n</tr>\n";

	}
	echo "</table>\n";
}
?>
