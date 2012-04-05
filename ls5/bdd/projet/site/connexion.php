<?php 
	session_start();
	$_TITRE_PAGE="BDD - connexion client";
	include("includes/in_entete"); 


	//$conn = oci_connect("log", "pass", "host:dbname");
	$conn = oci_connect("pittoli", "1712juph", "codd:PITTOLI");

	$query = "SELECT * from info_connect";
	if(! $conn)
	{
		echo "Erreur de connexion";
		exit;
	}
	$stmt = oci_parse($conn, $query);
	oci_execute($stmt);

?>
	<!-- container -->
	<div class="container">

		<?php include("includes/in_haut"); ?>

	</div>
<?php 
	include("includes/in_pied"); 
?>
