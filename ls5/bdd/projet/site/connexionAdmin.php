<?php 
	session_start();
	include("co");
	$_TITRE_PAGE="BDD - connexion admin";
	include("includes/in_entete"); 
?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>
		<div class="row">
			<div class="six columns">
				<form class="nice" action="co_admin.php" method="POST" >
					<fieldset>
					<h5>Connectez-vous !</h5>
					<p>Venez bosser.</p>
						<input id='c_login' name='c_login' type="text" placeholder="Login" class="input-text" />
						<input id='c_mdp' name='c_mdp' type="password" placeholder="Mot de passe" class="input-text" />
					</fieldset>
					<input type="submit" value="Connexion !" />
					<input type="reset" value="Oubliez-moi !" />
				</form>
			</div>
			<div class="six columns">
				<form class="nice" action="register.php" method="POST" >
					<fieldset>
					<h5>… ou enregistrez-vous !</h5>
					<p>Tellement de choses merveilleuses à faire quand on travaille chez nous !</p>
						<input id='r_login' name='r_login' type="text" placeholder="Login" class="input-text" />
						<input id='r_mdp' name='r_mdp' type="password" placeholder="Mot de passe" class="input-text" />
						<label for="r_compagnie">Compagnie</label>
						<select id="r_compagnie" name="r_compagnie">
<?php
$query = 'select * from CLIENT';
$stmt = oci_parse($conn, $query);

if( ! oci_execute($stmt))
{	
	die("Erreur connexion pour récup les compagnies");
}

oci_fetch_all($stmt, $row);
var_dump($row);

while($row = oci_fetch_assoc($stmt))
{
	var_dump($row);
	echo "<option value='" . 
		$row["IDCOMPAGNIE"] . "' > " . 
		$row["NOMCOMPAGNIE"]. "</option>\n";
}
?>
						</select>

					</fieldset>
					<input type="submit" value="Enregistrez-moi !" />
					<input type="reset" value="Oubliez-moi !" />
				</form>
			</div>
		</div>

	</div>
<?php include("includes/in_pied"); ?>
