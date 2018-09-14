<?php
include("includes/functions.php");

$sql = "SELECT whitelist.ReaderID, group_concat(whitelist.Uid) as UID_GROUP from whitelist group by whitelist.ReaderID";

if ($result=mysqli_query($conn,$sql))
  {
	  $show="";
	  $niz = array();

  while ($column=mysqli_fetch_row($result))
    {	

		$show .= $column[0] . "          | " . $column[1] . "\n";
		
    }
	
	echo "Reader ID's |  Card UID's\n";
	echo $show;

  mysqli_free_result($result);
}

?>