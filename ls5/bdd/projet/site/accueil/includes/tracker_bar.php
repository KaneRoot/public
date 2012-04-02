<?php

function active_tab($links)
{
	$nom_fichier = $_SERVER["SCRIPT_FILENAME"];
	preg_match("#.*\/(.*)#", $nom_fichier, $matches);

	$nom_fichier = $matches[1];
	
	echo "\n";
	foreach($links as $l)
	{
		$classe_active = (strcmp("$nom_fichier","$l.php") == 0) ? " class='active index-pages'" : " class='index-pages'";
		echo "\t\t\t\t\t<dd><a href='$l.php' $classe_active>$l</a></dd>\n";
	}
}
?>
			<div class="two columns">
				<dl class="nice tabs vertical hide-on-phones">	
					<?php
						$les_liens = array("profile", "aide", "torrents", "connexion");
						active_tab($les_liens);
					?>
				</dl>
			</div>
