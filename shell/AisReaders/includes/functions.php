<?php
include("config.php");


function addRte($logindex,$logaction,$readerid,$cardid,$systemid,$nfcuid,$uidlength,$timestamp)
{	
	$rl = "R";
    global $conn;
    $stmt = $conn->prepare("INSERT INTO all_logs (Log_index,Log_action,Reader_ID,Card_ID,System_ID,NFC_UID,UID_Length,Timestamp,RorL) VALUES (?,?,?,?,?,?,?,?,?)");
    $stmt->bind_param("isiiisiss",$logindex,$logaction,$readerid,$cardid,$systemid,$nfcuid,$uidlength,$timestamp,$rl);

    $stmt->execute();
}

function addLogs($logindex,$logaction,$readerid,$cardid,$systemid,$nfcuid,$uidlength,$timestamp)
{	
	$rl = "L";
    global $conn;
    $stmt = $conn->prepare("INSERT INTO all_logs (Log_index,Log_action,Reader_ID,Card_ID,System_ID,NFC_UID,UID_Length,Timestamp,RorL) VALUES (?,?,?,?,?,?,?,?,?)");
    $stmt->bind_param("isiiisiss",$logindex,$logaction,$readerid,$cardid,$systemid,$nfcuid,$uidlength,$timestamp,$rl);

    $stmt->execute();
}


function addAllLogs($logindex,$logaction,$readerid,$cardid,$systemid,$nfcuid,$uidlength,$timestamp)
{
    global $conn;
	$RL = "L";

    $stmt = $conn->prepare("INSERT INTO all_Logs (Log_Index,Log_action,Reader_ID,Card_ID,System_ID,NFC_UID,UID_Length,Timestamp,RorL) VALUES (?,?,?,?,?,?,?,?,?)");
    $stmt->bind_param("isiiisiss",$logindex,$logaction,$readerid,$cardid,$systemid,$nfcuid,$uidlength,$timestamp,$RL);

    $stmt->execute();
}

function addUnreadLog($logindex,$logaction,$readerid,$cardid,$systemid,$nfcuid,$uidlength,$timestamp)
{	
	$rl = "U";
    global $conn;
    $stmt = $conn->prepare("INSERT INTO all_logs (Log_index,Log_action,Reader_ID,Card_ID,System_ID,NFC_UID,UID_Length,Timestamp,RorL) VALUES (?,?,?,?,?,?,?,?,?)");
    $stmt->bind_param("isiiisiss",$logindex,$logaction,$readerid,$cardid,$systemid,$nfcuid,$uidlength,$timestamp,$rl);

	if($stmt->execute()){
			
		echo "ok";
	
	}else{
		
		echo $conn->error;
		
	}
}


?>
