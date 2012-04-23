<?php
	session_start();

/* La connexion est faite */
include("co.php");

/* si tout est bien rempli */
if(	isset($_POST['c_login']) && strlen($_POST['c_login']) > 0 &&
	isset($_POST['c_mdp']) && strlen($_POST['c_mdp']) > 0	)
{
	$_POST['c_login'] = "'" . $_POST['c_login'] . "'";
	$_POST['c_mdp'] = "'" . $_POST['c_mdp'] . "'";

	/* pas sécurisé */
	$query = "select * from GESTIONNAIRE where loginGestionnaire=" . $_POST['c_login'] . 
		"and mdpGestionnaire=" . $_POST['c_mdp'] ;

	$stmt = oci_parse($conn, $query);
	if( ! oci_execute($stmt))
		die("Il y a eu une erreur à la connexion du client.");

	if(oci_fetch_assoc($stmt))
	{
		/* Le type de connexion */
		$_SESSION['connexion'] = "gestionnaire";
		$_SESSION['login'] = $_POST['c_login'];
		header("Location: gestionnaire.php");
	}
	else
	{
		header("Location: connexionAdmin.php");
	}

}
