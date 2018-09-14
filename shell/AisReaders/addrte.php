<?php

include("includes/functions.php");

echo addRte($_POST["logindex"],$_POST["logaction"],$_POST["readerid"],$_POST["cardid"],$_POST["systemid"],$_POST["nfcuid"],$_POST["uidlength"],$_POST["timestamp"]);

?>