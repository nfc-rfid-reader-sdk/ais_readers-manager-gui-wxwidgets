<?php
//error_reporting(E_ERROR | E_PARSE);

include("includes/functions.php");
include("includes/config.php");

$json_str = file_get_contents('php://input');

$json_obj = json_decode($json_str, true);

for($i=0; $i< sizeof($json_obj); $i++)

{
	addAllLogs($json_obj[$i]["logindex"],$json_obj[$i]["logaction"],$json_obj[$i]["readerid"],$json_obj[$i]["cardid"],$json_obj[$i]["systemid"],$json_obj[$i]["nfcuid"],$json_obj[$i]["uidlength"],$json_obj[$i]["timestamp"]);
}

?>