<?php 

session_start();

include("co.php");
include("fonctions.php");

if(! isset($_GET['idvol'], $_GET['idcompagnie']))
{
	header("Location: consulter_vols.php");
}
$idvol = $_GET['idvol'];
$compagnie = $_GET['idcompagnie'];


$_TITRE_PAGE="BDD - Les billets (réservation, achat) ";

include("includes/in_entete"); 

$query = 
"select C.nomCompagnie as compagnie, V.idVol as idVol,
	to_char(V.dateArrivee, 'yyyy/mm/dd hh24:mi:ss') as datearrivee,	
	to_char(V.dateDepart, 'yyyy/mm/dd hh24:mi:ss') as datedepart
from VOL V JOIN COMPAGNIE C ON C.idCompagnie = V.idCompagnie
where V.idVol=:idvol and V.idCompagnie=:compagnie ";

$stmt = oci_parse($conn, $query);
oci_bind_by_name($stmt, ':idvol', $idvol);
oci_bind_by_name($stmt, ':compagnie', $compagnie);

if(! oci_execute($stmt))
	die("Erreur à la récupération des billets.");

if( ! $row = oci_fetch_assoc($stmt))
	die("Erreur à la recherche d'info sur les billets.");

	$nomcompagnie = $row['COMPAGNIE'];
	$datedepart = $row['DATEDEPART'];
	$datearrivee = $row['DATEARRIVEE'];

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

		<div class="row">
		<?php 
echo "<h5>Les billets du vol $idvol de la compagnie $nomcompagnie. </h5>";
	   	?>
			<div class="seven columns panel">
<?php
achat_billet($conn);
reservation_billet($idvol, $compagnie, $conn);
afficher_billets($idvol, $compagnie, $conn);
?>
			</div>
			<div class='four columns panel'>

<?php echo "<p>Départ le $datedepart. <br />Arrivée le $datearrivee. </p>"; ?>
			</div>
		</div>
	</div>
<?php include("includes/in_pied"); ?>
