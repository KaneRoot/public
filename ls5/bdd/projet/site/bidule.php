<?php 
	//$conn = oci_connect("log", "pass", "host:dbname");
	$conn = oci_connect("kalk", "kalk", "localhost/ROSA");
	if(! $conn)
	{
		echo "Erreur de connexion";
		exit;
	}

	$query = "select * from Utilisateur";
	$stmt = oci_parse($conn, $query);
	oci_execute($stmt);

	echo "vous êtes : ". $_SERVER["REMOTE_ADDR"] . "\n<br/>";
	while($array = oci_fetch_assoc($stmt))
	{
		echo "<li><ul>";

		foreach(array_keys($array) as $key)
			echo "<li>" . $key . " " . $array[$key]. "</li>\n";

		echo "</ul></li>";
	}

?>
