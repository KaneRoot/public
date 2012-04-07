<?php 
	session_start();
	$_TITRE_PAGE="BDD - connexion client";
	include("includes/in_entete"); 
?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>
	
		<div class="row">
			<div class="six columns">
				<form class="nice" action="co_cli.php" method="POST" >
					<fieldset>
					<h5>Connectez-vous !</h5>
					<p>Tellement de choses merveilleuses à faire quand on est connecté !</p>
						<input id='c_login' type="text" placeholder="Login" class="input-text" />
						<input id='c_mdp' type="password" placeholder="Mot de passe" class="input-text" />
					</fieldset>
				</form>
			</div>
			<div class="six columns">
				<form class="nice" action="register.php" method="POST" >
					<fieldset>
					<h5>… ou enregistrez-vous !</h5>
					<p>Tellement de choses merveilleuses à faire quand on est client !</p>
						<input id='r_nom' type="text" placeholder="Nom" class="input-text" />
						<input id='r_prenom' type="text" placeholder="prenom" class="input-text" />
						<input id='r_adresse' type="text" placeholder="adresse" class="input-text" />
						<input id='r_numtel' type="text" placeholder="numtel" class="input-text" />
						<input id='r_login' type="text" placeholder="Login" class="input-text" />
						<input id='r_mdp' type="password" placeholder="Mot de passe" class="input-text" />
					</fieldset>
				</form>
			</div>
		</div>

	</div>
<?php 
	include("includes/in_pied"); 
?>
