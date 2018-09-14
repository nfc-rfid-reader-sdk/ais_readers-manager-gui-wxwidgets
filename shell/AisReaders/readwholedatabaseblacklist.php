<?php
include("includes/functions.php");

$sql = "SELECT blacklist.ReaderID, group_concat(blacklist.CardID) as CardID_GROUP from blacklist group by blacklist.ReaderID";

if ($result=mysqli_query($conn,$sql))
  {
	  $show="";
	  $niz = array();

  while ($column=mysqli_fetch_row($result))
    {	

		$show .= $column[0] . "          | " . $column[1] . "\n";
		
    }
	echo "Reader ID's |  Card ID's\n";
	echo $show;

  mysqli_free_result($result);
}

?>