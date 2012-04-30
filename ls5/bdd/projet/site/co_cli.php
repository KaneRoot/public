<?php
	session_start();

/* La connexion est faite */
include("co.php");

/* si tout est bien rempli */
if(	isset($_POST['c_login'], $_POST['c_mdp']) && strlen($_POST['c_login']) > 0 &&
	strlen($_POST['c_mdp']) > 0	)
{
	$login = $_POST['c_login'] ;
	$mdp = $_POST['c_mdp'] ;

	$query = "select * from CLIENT 
		where loginClient=:login and mdpClient=:mdp" ;

	$stmt = oci_parse($conn, $query);
	oci_bind_by_name($stmt, ':login', $login);
	oci_bind_by_name($stmt, ':mdp', $mdp);

	if( ! oci_execute($stmt))
		die("Il y a eu une erreur à la connexion du client.");

	if($row = oci_fetch_assoc($stmt))
	{
		/* Le type de connexion */
		$_SESSION['connexion'] = "client";
		$_SESSION['login'] = $login;
		$_SESSION['idclient'] = $row['IDCLIENT'];

		header("Location: client.php");
	}
	else
	{
		header("Location: connexion.php");
	}

}
else
{
	header("Location: connexion.php");
}
