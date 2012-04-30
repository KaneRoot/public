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
			<h5>Vos réservations en cours</h5>
			<hr />
			<div class="eight columns">
<?php
achat_billet($conn);
afficher_reservations($conn);
?>
			</div>
			<div class="three columns">
				<h4 class="green radius label" >Bienvenue cher client !</h4>
				<hr />
				<p>Here are your options.</p>
				<hr />
				<p><a href="reservation.php" class="nice large radius red button">Reserver</a><br /> </p>
				<p><a href="consulter_vols.php" class="nice large radius blue button">Voir les vols</a></p>
			</div>
		</div>
		<div class="row">
			<h5>Vos achats passés</h5>
			<hr />
			<div class="ten columns">
<?php
afficher_achats($conn);
?>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
