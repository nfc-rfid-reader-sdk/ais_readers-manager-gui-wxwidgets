<?php

include("includes/config.php");

$nfcuid = $_POST["blUID"];
$readerid = $_POST["blReaderId"];


	global $conn;
    $stmt = $conn->prepare("INSERT INTO blacklist (CardID,ReaderID) VALUES (?,?)");
    $stmt->bind_param("si",$nfcuid,$readerid);

    if ($stmt->execute()) {

        echo "ok";

    } else {
        echo "error: " . $stmt->error;
	}


?>