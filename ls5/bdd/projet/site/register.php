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
	if(existe(array($_POST['r_compagnie'])))
	{
		$query = "insert into GESTIONNAIRE VALUES(seq_gestionnaire,". $_POST['r_login'] . 
			", " . $_POST['r_mdp'] . ", " . $_POST['r_compagnie'] . " )";
		$stmt = oci_parse($conn, $query);
		if( ! oci_execute($stmt))
			die("Il y a eu une erreur dans l'insertion d'un nouveau gestionnaire.");
	}
	else if(existe(array($_POST['r_nom'], $_POST['r_prenom'], $_POST['r_adresse'], $_POST['r_numtel'])))
	{
		$query = "insert into CLIENT VALUES(seq_client, ". $_POST['r_login'] . ", " . 
			$_POST['r_mdp'] . ", " . $_POST['r_nom'] . ", " . $_POST['r_prenom'] . ", " . 
			$_POST['r_adresse'] . ", ". $_POST['r_numtel']. " )";
		$stmt = oci_parse($conn, $query);
		if( ! oci_execute($stmt))
			die("Il y a eu une erreur dans l'insertion d'un nouveau client.");
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
