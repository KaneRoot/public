<?php 
	$_TITRE_PAGE="BDD - accueil";
	include("includes/in_entete"); 
?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
			<div class="five columns panel">
				<h4>Bienvenue !</h4>
				<dl class="tabs">
					<dd><a href="#connexion" class="active">Connexion</a></dd>
					<dd><a href="#connexionAdmin">Connexion Admin</a></dd>
				</dl>

				<ul class="tabs-content">
					<li class="active" id="connexionTab"><p>Connexion du client.</p></li>
					<li id="connexionAdminTab"><p>Connexion des administrateurs (les compagnies).</p></li>
				</ul>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
