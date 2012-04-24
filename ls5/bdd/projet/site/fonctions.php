<?php

/* pas secure */
function getCompagnie()
{
	if(! isset($conn))
		include('co.php');

	$query = "select idCompagnie 
	from GESTIONNAIRE
	where UPPER(loginGestionnaire) = UPPER( " . $_SESSION['login'] . ")";

	$stmt = oci_parse($conn, $query);
	if( ! oci_execute($stmt))
	die("Il y a eu une erreur dans la recherche de la compagnie du gestionnaire.");

	if( ! ( $row = oci_fetch_assoc($stmt)))
	die("Il y a eu une erreur dans la recherche de la compagnie du gestionnaire.");

	$compagnie = $row['IDCOMPAGNIE'];

	return $compagnie;
}
function estGestionnaire()
{
	if(! isset($_SESSION['connexion'], $_SESSION['login']) || strcmp($_SESSION['connexion'] , "gestionnaire") != 0 )
	{
		header("Location: connexionAdmin.php");
	}
}
function modifierVol( $idvol, $idcompagnie )
{
	if(isset($_POST['villedepart'], $_POST['villearrivee'], 
				$_POST['datedepart'], $_POST['datearrivee']))
	{
		$villedepart = $_POST['villedepart'];
		$villearrivee = $_POST['villearrivee'];
		$datedepart = "to_date( '". $_POST['datedepart'] . "' ,'yyyy/mm/dd hh24:mi:ss' )";
		$datearrivee = "to_date( '". $_POST['datearrivee'] . "' ,'yyyy/mm/dd hh24:mi:ss' )";

		$query = "update VOL set idVilleDepart=$villedepart ,
			idVilleArrivee=$villearrivee ,
			dateDepart=$datedepart ,
			dateArrivee=$datearrivee 
			where idVol=$idvol and idCompagnie=$compagnie";
		
		$stmt = oci_parse($conn, $query);
		if(! oci_execute($stmt))
			die("Erreur à l'update de la table. <br /> $query");
	}
}
?>
