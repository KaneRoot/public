<?php 

session_start();

include("co.php");
include("fonctions.php");


/* on s'assure que la personne est connectée et gestionnaire */
if(estGestionnaire())
{
	$compagnie = getCompagnie();
	$_TITRE_PAGE="BDD - vols de la compagnie";
}
else
{
	$_TITRE_PAGE="BDD - vols";
}
include("includes/in_entete"); 

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
		<?php
			if(estGestionnaire())
			{
				echo "<h5>Visuel sur l'ensemble de nos vols.</h5>\n";
			}
			else
			{
				echo "<h5>Visuel sur l'ensemble des vols.</h5>\n";
			}
		?>
			
			<div class="twelve columns panel">
<?php
afficher_les_vols($conn);
?>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
