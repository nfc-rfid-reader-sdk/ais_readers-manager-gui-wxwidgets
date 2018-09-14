<?php
include("includes/functions.php");

$id = $_POST["id"];

$sql = "SELECT whitelist.ReaderID, group_concat(whitelist.Uid) as UID_GROUP from whitelist where whitelist.ReaderID =".$id . " group by whitelist.ReaderID";

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