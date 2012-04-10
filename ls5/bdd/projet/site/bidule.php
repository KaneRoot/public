<?php 
	//$conn = oci_connect("log", "pass", "host:dbname");

	$conn = oci_connect("pittoli", "1712juph", "localhost/ROSA");
	if(! $conn) 
	{
		echo "Erreur de connexion";
		exit;
	}
	$query = 'select * from CLIENT';
	$stmt = oci_parse($conn, $query);

	if( ! oci_execute($stmt))
	{	
		die("Erreur connexion pour récup les compagnies");
	}

	while($array = oci_fetch_assoc($stmt))
	{
		echo "<li><ul>";

		foreach(array_keys($array) as $key)
			echo "<li>" . $key . " " . $array[$key]. "</li>\n";

		echo "</ul></li>";
	}
var_dump($array);
?>
