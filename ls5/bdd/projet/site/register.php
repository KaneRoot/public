<?php

function existe($val)
{
	$retour = true;
	foreach($val as $v)
	{
		if(! (isset($v) && strlen($v) != 0))
			$retour = false;
	}
	return $retour;
}

include("co");

// Quelqu'un tente de s'enregistrer
if(existe(array($_POST['r_login'], $_POST['r_mdp'])))
{
	if(isset($_POST['r_compagnie']) && strlen($_POST['r_compagnie']) != 0 )
	{
		$query = "insert into GESTIONNAIRE VALUES(seq_gestionnaire,". $_POST['r_login'] . 
			", " . $_POST['r_mdp'] . ", " . $_POST['r_compagnie'] . " )";
		$stmt = oci_parse($conn, $query);
		if( ! oci_execute($stmt))
			die("Il y a eu une erreur dans l'insertion d'un nouveau gestionnaire.");

		$_SESSION['estCli'] = false;
		$_SESSION['login'] = $_POST['r_login'];
		$_SESSION['compagnie'] = $_POST['r_compagnie'];

		echo "<p><a href='gestionnaire.php' >Aller sur la page d'accueil.</a></p>";
	}
	else if(existe(array($_POST['r_nom'], $_POST['r_prenom'], $_POST['r_adresse'], $_POST['r_numtel'])))
	{
		$query = "insert into CLIENT VALUES(seq_client, ". $_POST['r_login'] . ", " . 
			$_POST['r_mdp'] . ", " . $_POST['r_nom'] . ", " . $_POST['r_prenom'] . ", " . 
			$_POST['r_adresse'] . ", ". $_POST['r_numtel']. " )";
		$stmt = oci_parse($conn, $query);
		echo "\n<br />La requête : ". $query . "<br />\n";
		if( ! oci_execute($stmt))
			die("Il y a eu une erreur dans l'insertion d'un nouveau client.");

		$_SESSION['estCli'] = true;
		$_SESSION['login'] = $_POST['r_login'];
		$_SESSION['nom'] = $_POST['r_nom'];
		$_SESSION['prenom'] = $_POST['r_prenom'];

		echo "<p><a href='client.php' >Aller sur la page d'accueil.</a></p>";
	}
	else
	{
		echo "Petit problème… vous n'avez pas entré les bons champs.";
	}
}
else
{
	echo "<p>Petit problème… vous n'avez pas entré les bons champs. Retournez à la page précédente !</p>";
}

?>
