<?php

session_start();

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

include("co.php");

if(! isset($_SESSION['connexion']))
{
	// Quelqu'un tente de s'enregistrer
	if(existe(array($_POST['r_login'], $_POST['r_mdp'])))
	{
		/* Pour la connexion automatique */
		$login = $_POST['r_login'] ;
		$mdp = $_POST['r_mdp'];

		// Enregistrement d'un gestionnaire
		if(isset($_POST['r_compagnie']) && strlen($_POST['r_compagnie']) != 0 )
		{
			$compagnie = $_POST['r_compagnie'];
			$query = "insert into GESTIONNAIRE VALUES(seq_gestionnaire.nextVal,
				:login, :mdp, :compagnie)";

			$stmt = oci_parse($conn, $query);
			oci_bind_by_name($stmt, ':login', $login);
			oci_bind_by_name($stmt, ':mdp', $mdp);
			oci_bind_by_name($stmt, ':compagnie', $compagnie);

			if( ! oci_execute($stmt))
				die("Il y a eu une erreur dans l'insertion d'un nouveau gestionnaire.");

			/* si un gestionnaire s'est enregistré, il est connecté automatiquement */
			$_SESSION['connexion'] = "gestionnaire";
			$_SESSION['login'] = $login;
			$_SESSION['compagnie'] = $compagnie;

			header("Location: gestionnaire.php");
		}
		// Enregistrement d'un client
		else if(existe(array($_POST['r_nom'], $_POST['r_prenom'], $_POST['r_adresse'])))
		{
			$nom = $_POST['r_nom'] ;
			$prenom = $_POST['r_prenom'];
			$adresse = $_POST['r_adresse'];
			$numtel = $_POST['r_numtel'];

			$query = "insert into CLIENT VALUES(seq_client.nextVal, 
				:login, :mdp, :nom, :prenom, :adresse, :numtel)" ;
			$stmt = oci_parse($conn, $query);
			oci_bind_by_name($stmt, ':login', $login);
			oci_bind_by_name($stmt, ':mdp', $mdp);
			oci_bind_by_name($stmt, ':nom', $nom);
			oci_bind_by_name($stmt, ':prenom', $prenom);
			oci_bind_by_name($stmt, ':adresse', $adresse);
			oci_bind_by_name($stmt, ':numtel', $numtel);

			if( ! oci_execute($stmt))
				die("Il y a eu une erreur dans l'insertion d'un nouveau client.");

			/* si un client s'enregistre, il est connecté automatiquement */
			$_SESSION['connexion'] = "client";
			$_SESSION['login'] = $login;
			$_SESSION['nom'] = $nom;
			$_SESSION['prenom'] = $prenom;

			$query = "select idClient from CLIENT where loginClient=:login";
			$stmt = oci_parse($conn, $query);
			oci_bind_by_name($stmt, ':login', $login);
			if( ! oci_execute($stmt))
				die("Il y a eu une erreur dans l'insertion d'un nouveau client.");

			if( ! ( $row = oci_fetch_assoc($stmt)))
				die("Il y a eu une erreur dans l'insertion d'un nouveau client.");

			$_SESSION['idclient'] = $row['IDCLIENT'];


			header("Location: client.php");
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
}
else
{
	echo "Vous êtes déjà connecté !";
}

?>
