<?php
include("includes/functions.php");

$id = $_POST["id"];

$sql = "SELECT blacklist.ReaderID, group_concat(blacklist.CardID) as CardID_GROUP from blacklist where blacklist.ReaderID =" . $id . " group by blacklist.ReaderID";

if ($result=mysqli_query($conn,$sql))
  {
	  $show="";
	  $niz = array();

  while ($column=mysqli_fetch_row($result))
    {	
		$show .= $column[1];
    }
	
	echo $show;
 
  mysqli_free_result($result);
}

?>