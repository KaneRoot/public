<?php 

session_start();

include("co.php");
include("fonctions.php");

/* on s'assure que la personne qui arrive ici est bien gestionnaire */
verifier_est_gestionnaire();

if(! isset($_GET['idvol']) || $_GET['idvol'] < 0)
{
	header("Location: vols_global.php");
}

$idvol = $_GET['idvol'];
$compagnie = getCompagnie();

$_TITRE_PAGE="BDD - modifications des vols et billets";
include("includes/in_entete"); 

/* se charge de faire la vérification 
   si on souhaite ou non réellement modifier le vol */
modifierVol($idvol, $compagnie, $conn);

/* se charge également de faire la vérification
   si on souhaite ou pas ajouter des billets */
ajout_billet($idvol, $compagnie, $conn);

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
			<h5>Modification d'un vol</h5>
			<hr />
			<form class="nice" action="modifier_vols.php?idvol=<?php echo $idvol; ?>" method="POST" >
			<div class="five columns panel">
<?php echo "<p>On souhaite modifier le vol $idvol de la compagnie $compagnie .</p>\n"; ?>

<?php
/* On récupère les informations utiles */
$query = "select 
	idVilleDepart, 
	idVilleArrivee, 
	to_char(dateDepart, 'yyyy/mm/dd hh24:mi:ss') as ledatedepart, 
	to_char(dateArrivee, 'yyyy/mm/dd hh24:mi:ss') as ledatearrivee 
from VOL 
where idCompagnie=$compagnie and idVol=$idvol";

$stmt = oci_parse($conn, $query);
if(! oci_execute($stmt))
	die("Erreur à la récupération des informations sur le vol.");

if(! ($row = oci_fetch_assoc($stmt)))
	die("Nous n'avons pas trouvé le vol en question ! ");

/* On va chercher les villes */
$query = "select idVille, nomVille from VILLE";
$stmt = oci_parse($conn, $query);
if(! oci_execute($stmt))
	die("Erreur à la récupération des informations sur les villes.");

$options_depart = "";
$options_arrivee = "";

while($ligne = oci_fetch_assoc($stmt))
{
	$options_depart .= "<option value='" . $ligne['IDVILLE'] . "' " ;
	$options_arrivee .= "<option value='" . $ligne['IDVILLE'] . "' " ;

	if($ligne['IDVILLE'] == $row['IDVILLEDEPART'])
		$options_depart .= "selected=selected ";

	if($ligne['IDVILLE'] == $row['IDVILLEARRIVEE'])
		$options_arrivee .= "selected=selected ";

	$options_depart .= " >". $ligne['NOMVILLE'] . "</option>\n";
	$options_arrivee .= " >". $ligne['NOMVILLE'] . "</option>\n";
}

?>
					<label for='villedepart' class="blue radius label" >La ville de départ</label><br />
					<select id="villedepart" name="villedepart">
					<?php echo $options_depart; ?>
					</select>

					<label for='villearrivee' class="blue radius label" >La ville d'arrivée</label><br />
					<select id="villearrivee" name="villearrivee">
					<?php echo $options_arrivee; ?>
					</select>

				</div>
				<div class="five columns panel">

					<label for='datedepart' class="blue radius label" >La date de départ</label><br />
					<input id='datedepart' name='datedepart' type="text" value="<?php 
					echo $row['LEDATEDEPART'] ; ?>" class="input-text" />
					<label for='datearrivee' class="blue radius label" >La date d'arrivée</label><br />
					<input id='datearrivee' name='datearrivee' type="text" value="<?php 
					echo $row['LEDATEARRIVEE'] ; ?>" class="input-text" />

					<input type="submit" value="Modifier ce vol !" />
					<input type="reset" value="Oublier ça" />
				</div>
			</form>
		</div>
		<div class="row">
			<h5>Escales</h5>
			<hr />
			<div class="six columns panel">
<?php
	suppression_escale($idvol, $compagnie, $conn);
	ajout_escale($idvol, $compagnie, $conn);
	afficher_escales($idvol, $compagnie, $conn);
?>
			</div>
			<div class="five columns panel">
<?php
	afficher_ajout_escale($idvol, $compagnie, $conn);
?>
			</div>
		</div>
		<div class="row">
			<h5>Les billets associés à ce vol</h5>
			<hr />
			<div class="six columns panel">
<?php
	suppression_billet($idvol, $compagnie, $conn);
	afficher_billets($idvol, $compagnie, $conn);
?>
			</div>
			<div class="five columns panel">
			<h5>Ajouter un billet</h5>
			<form class="nice" action="?idvol=<?php echo $idvol; ?>" method="POST" >
			<fieldset>
				<label for='prix' class="blue radius label" >Le prix du billet</label><br />
				<input id='prix' name='prix' class="input-text" type="text" placeholder="Le prix du billet" />
				<label for='promotion' class="blue radius label" >La promotion du billet</label><br />
				<input id='promotion' class="input-text" name='promotion' type="text" placeholder="La promotion" />
				<input type="submit" value="Ajouter ce billet" />
				<input type="reset" value="Oublier ça" />
			</fieldset>
			</form>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
