<html>
<head>
<?php

echo "hi there!<br \>\n";

/*if($_GET['info'])
{
	$info = strip_tags($_GET['info']);

	$codes_array = array(
		"a3" => "GuessTheAnimal",
		"a2" => "BongoBonanza",
		"a1" => "NutcrackerPuppet"
	);
	$exhibit = $codes_array[$info];
	echo "OK-1<br \>\n";
	$command = file_put_contents("exhibits.txt", $exhibit . "\n", FILE_APPEND);
//	echo "OK-2<br \>\n";
//	echo $exhibit . "<br \>\n";
//	echo "OK-3<br \>\n";
//	echo "bytes: " . $command . "<br \>\n";
//	echo "OK-4<br \>\n";

	$newURL = 'http:/' . '/130.64.95.38/slideshow.php?exhibit=' . $exhibit;

}*/

if($_GET['id'])
{
        $id = strip_tags($_GET['id']);

        $codes_array = array(
                "a3" => "GuessTheAnimal",
                "a2" => "BongoBonanza",
                "a1" => "NutcrackerPuppet"
        );
        $exhibit = $codes_array[$id];
        echo "OK-2<br \>\n";
        $command = file_put_contents("exhibits.txt", $exhibit . "\n", FILE_APPEND);
//      echo "OK-2<br \>\n";
//      echo $exhibit . "<br \>\n";
//      echo "OK-3<br \>\n";
//      echo "bytes: " . $command . "<br \>\n";
//      echo "OK-4<br \>\n";

        $newURL = 'http:/' . '/130.64.95.38/slideshow.php?exhibit=' . $exhibit;

}

if($_GET['redir'])
{
	echo "redir was here!";
}

/*if($_GET['redir'])
{
	//If signal comes from non-Arduino: pull up webpage on source device
	<script language=JavaScript>window.location.href="<?php echo $newURL ?>"</script>
}*/

?>
</head></html>
