<?php

	function getTimeFromNTP($host = 'pool.ntp.org', $timeout = 10)
	{
		$socket = stream_socket_client('udp://' . $host . ':123', $errno, $errstr, (int)$timeout);
		$msg = "\010" . str_repeat("\0", 47);
		fwrite($socket, $msg);
		$response = fread($socket, 48);
		fclose($socket);
	
		$data = unpack('N12', $response);
		
		$timestamp = sprintf('%u', $data[9]);
		
		$timestamp -= 2208988800;
		return $timestamp;
			
	}

echo getTimeFromNTP();

?>