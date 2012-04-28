<?php 

session_start();

if(! isset($_SESSION['connexion']))
{
	/* si on n'est pas connecté */
	header("Location: connexion.php");
}
elseif( 0 != strcmp("client", $_SESSION['connexion']) )
{
	/* si on est connecté mais qu'on est gestionnaire */
	header("Location: gestionnaire.php");
}

	$_TITRE_PAGE="BDD - accueil client";
	include("includes/in_entete"); 
?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
			<div class="five columns panel">
				<h4>Bienvenue cher client!</h4>
				<p>Here are your options.</p>
				<p>
				<a href="reservation.php" class="nice small radius blue button">Reserver un vol</a><br /><br />
				<a href="consulter_vols.php" class="nice small radius blue button">Voir les vols</a><br />
				</p>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
