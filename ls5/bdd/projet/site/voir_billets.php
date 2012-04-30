<?php 

session_start();

include("co.php");
include("fonctions.php");

if(! isset($_GET['idvol'], $_GET['idcompagnie']))
{
	header("Location: consulter_vols.php");
}
$idvol = $_GET['idvol'];
$compagnie = $_GET['idcompagnie'];


$_TITRE_PAGE="BDD - Les billets (réservation, achat) ";

include("includes/in_entete"); 

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
		<?php echo "<h5>Les billets du vol $idvol de la compagnie $compagnie </h5>"; ?>
			<div class="twelve columns panel">
<?php
achat_billet($conn);
reservation_billet($idvol, $compagnie, $conn);
afficher_billets($idvol, $compagnie, $conn);
?>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
