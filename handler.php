<?php
echo "hello there!";
if($_GET['info'])
{
	echo "hello";
	$info = strip_tags($_GET['info']);

	$codes_array = array(
		"a2" => "AlienRescue",
		"a1" => "SteakSauce"
	);
	$exhibit = $codes_array[$info];
	echo $exhibit;
	$result = shell_exec($command);
	file_put_contents("exhibits.txt", $exhibit, FILE_APPEND);
}
?>
