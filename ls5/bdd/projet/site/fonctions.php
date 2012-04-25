<?php

/* pas secure */
function getCompagnie()
{
	if(! isset($conn))
		include('co.php');

	$query = "select idCompagnie 
	from GESTIONNAIRE
	where UPPER(loginGestionnaire) = UPPER( " . $_SESSION['login'] . ")";

	$stmt = oci_parse($conn, $query);
	if( ! oci_execute($stmt))
	die("Il y a eu une erreur dans la recherche de la compagnie du gestionnaire.");

	if( ! ( $row = oci_fetch_assoc($stmt)))
	die("Il y a eu une erreur dans la recherche de la compagnie du gestionnaire.");

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
		$promotion = "NULL";

		if(isset($_POST['promotion']))
			$promotion = $_POST['promotion'];

		$query =
		"insert into BILLET VALUES(seq_billet.nextVal, $idvol, $compagnie,
			$prix, $promotion, NULL)";
		
		$stmt = oci_parse($conn, $query);
		if(! oci_execute($stmt))
			die("Erreur à l'update de la table. <br /> $query");
	}
}
function get_prochain_idvol($conn)
{
	$compagnie = getCompagnie();
	$query = "select max(idVol)+1 as prochainid from VOL where idCompagnie=$compagnie";
	$stmt = oci_parse($conn, $query);
	if(! oci_execute($stmt))
		die("Erreur à l'update de la table. <br /> $query");
	$row = oci_fetch_assoc($stmt);

	return $row['PROCHAINID'];
}
function afficher_les_vols($conn)
{
	/* À FINIR TODO */
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
	}
	if(estGestionnaire())
		$compagnie = getCompagnie();

	/* requête un peu complexe */
	$query = 
	"select 
		V.idVol as idvol, 
		C.nomCompagnie as compagnie, 
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

	if(isset($compagnie))
		$query .= " and V.idCompagnie=$compagnie ";

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
					<th>Compagnie</th>
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
				</tr>
			</thead>

	<?php
	while($row = oci_fetch_assoc($stmt))
	{
		echo "<tr>";
		echo	"<td>" . $row['IDVOL'] . "</td>" .
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

		echo "</tr>\n";
	}

	?>
		</table>
	<?php
}
function afficher_billets($idvol, $compagnie, $conn)
{
	?>
				<table>
					<thead>
						<th>id</th>
						<th>Prix</th>
						<th>Promo</th>
						<th>État</th>
					</thead>

<?php
$query = "select * from BILLET
where idVol = " . $idvol . " and idCompagnie=" . $compagnie ;

$stmt = oci_parse($conn, $query);
if(! oci_execute($stmt))
	die("Erreur à la récupération des billets.");

while($row = oci_fetch_assoc($stmt))
{
	echo "<tr>";
	echo 
		"<td>" . $row['IDBILLET'] . "</td>" .
		"<td>" . $row['PRIX'] . "</td>" .
		"<td>" . $row['PROMO'] . "</td>" .
		"<td>" . $row['ETATBILLET'] . "</td>";
	echo "</tr>\n";

}

?>
				</table>
	<?php
}
?>
