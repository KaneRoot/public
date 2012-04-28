<?php 

session_start();

if(! isset($_SESSION['connexion']))
{
	/* si on n'est pas connecté */
	header("Location: connexionAdmin.php");
}
elseif( 0 != strcmp("gestionnaire", $_SESSION['connexion']) )
{
	/* si on est connecté mais qu'on est gestionnaire */
	header("Location: client.php");
}

	$_TITRE_PAGE="BDD - accueil gestionnaire";
	include("includes/in_entete"); 
?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
			<div class="three columns panel">
				<h4>Travaille plus vite !</h4>
				<p>Here are your options.</p>

				<hr />
		<p>
<a href="ajout_vol.php" class="nice small radius blue button">Ajouter un vol</a><br />
<a href="ajout_ville.php" class="nice small radius blue button">Ajouter une ville</a><br />
<a href="vols_global.php" class="nice small radius blue button">Voir les vols</a><br />
		</p>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
