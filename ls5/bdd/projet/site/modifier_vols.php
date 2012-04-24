<?php 

session_start();

include("co.php");
include("fonctions.php");

/* on s'assure que la personne qui arrive ici est bien gestionnaire */
estGestionnaire();

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
modifierVol($idvol, $idcompagnie, $conn);

/* se charge également de faire la vérification
   si on souhaite ou pas ajouter des billets */
ajoutBillet($idvol, $idcompagnie, $conn);

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
			<h5>Modification d'un vol</h5>
			<hr />
			<div class="five columns panel">
<?php echo "<p>On souhaite modifier le vol $idvol de la compagnie $compagnie .</p>"; ?>
			<form class="nice" action="modifier_vols.php?idvol=<?php echo $idvol; ?>" method="POST" >

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
<p>Ville de départ</p>
<select id="villedepart" name="villedepart">
<?php echo $options_depart; ?>
</select>

<p>Ville d'arrivée</p>
<select id="villearrivee" name="villearrivee">
<?php echo $options_arrivee; ?>
</select>

</div>
<div class="five columns panel">

<p>Date de départ </p>
<input id='datedepart' name='datedepart' type="text" value="
	<?php echo $row['LEDATEDEPART'] ; ?> " class="input-text" />
<p>Date d'arrivée </p>
<input id='datearrivee' name='datearrivee' type="text" value="
	<?php echo $row['LEDATEARRIVEE'] ; ?> " class="input-text" />

<input type="submit" value="Modifier ce vol !" />
<input type="reset" value="Oublier ça" />
			</form>
			</div>
		</div>
		<div class="row">
			<h5>Les billets associés à ce vol</h5>
			<hr />
			<div class="six columns panel">
			</div>
			<div class="five columns panel">

			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
