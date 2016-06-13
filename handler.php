<?php
//echo "hello there!";
if($_GET['info'])
{
	$info = strip_tags($_GET['info']);

	$codes_array = array(
		"a4" => " ",
		"a3" => " ",
		"a2" => "AlienRescue",
		"a1" => "SteakSauce"
	);
	$exhibit = $codes_array[$info] . "\n";
	echo "OK!";
	$result = shell_exec($command);
	file_put_contents("exhibits.txt", $exhibit, FILE_APPEND);
}
?>
