#Create a simulator object
set ns [new Simulator]

#Define different colors for data flows (for NAM)
$ns color 1 green
$ns color 2 Blue

#Open the NAM trace file
set nf [open out.nam w]
$ns namtrace-all $nf

#Open the Trace file
set tf [open out.tr w]
$ns trace-all $tf

#Define a 'finish' procedure
proc finish {} {
	global ns nf
	$ns flush-trace
	#Close the NAM trace file
	close $nf
	#Execute NAM on the trace file
	exec nam out.nam &
	exit 0
}

#Create seven nodes
set n0 [$ns node]
set n1 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
#Create links between the nodes
$ns duplex-link $n0 $n5 10Mb 5ms DropTail
$ns duplex-link $n1 $n5 10Mb 5ms DropTail
$ns duplex-link $n5 $n4 10Mb 5ms DropTail
$ns duplex-link $n4 $n3 10Mb 5ms DropTail
$ns duplex-link $n7 $n6 10Mb 5ms DropTail
$ns duplex-link $n6 $n5 10Mb 5ms DropTail

#Set Queue Size of link (n1-n5) to 10
#$ns queue-limit $n5 $n3 10
#$ns queue-limit $n5 $n0 10

#Give node position (for NAM)
$ns duplex-link-op $n7 $n6 orient right
$ns duplex-link-op $n7 $n6 label "FTP/TCP"
$ns duplex-link-op $n4 $n3 orient right
$ns duplex-link-op $n1 $n5 orient right-down
$ns duplex-link-op $n1 $n5 label "CBR/UDP"
$ns duplex-link-op $n5 $n0 orient right-down
$ns duplex-link-op $n6 $n5 orient right-up
$ns duplex-link-op $n5 $n4 orient right-up

#Monitor the queue for link (n1-n5). (for NAM)
#$ns duplex-link-op $n1 $n5 queuePos 0.5

#Setup a TCP connection
set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n7 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n3 $sink
$ns connect $tcp $sink
$tcp set fid_ 1

#Setup a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

#Setup a UDP connection
set udp [new Agent/UDP]
$ns attach-agent $n1 $udp
set null [new Agent/Null]
$ns attach-agent $n0 $null
$ns connect $udp $null
$udp set fid_ 2

#Setup a CBR over UDP connection
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1mb
$cbr set random_ false

#Schedule events for the CBR and FTP agents
$ns at 0.1 "$cbr start"
$ns at 0.2 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 4.5 "$cbr stop"





#Detach tcp and sink agents (not really necessary)
$ns at 4.5 "$ns detach-agent $n0 $sink; $ns detach-agent $n3 $sink"

#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"

#Print CBR packet size and interval
puts "CBR packet size = [$cbr set packet_size_]"
puts "CBR interval = [$cbr set interval_]"

#Run the simulation
$ns run

