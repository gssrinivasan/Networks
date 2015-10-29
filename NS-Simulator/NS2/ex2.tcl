set val(chan) Channel/WirelessChannel ;
set val(prop) Propogation/TwoRayGround ;
set val(netif) Phy/WirelessPhy ;
set val(mac) Mac/802_11 ;
set val(ifq) Queue/DropTail/PriQueue ;
set val(ll) LL ;
set val(ant) Antenna/OmniAntenna ;
set val(ifqlen) 50 ;
set val(nn) 15 ;
set val(rp) AODV ;
set val(x) 500 ;
set val(y) 400 ;
set val(stop) 150 ;
set ns_ [new Simulator]

$ns_ use-newtrace
$ns_ tracefd [open simple.tr w]
$ns_ windowVsTime2 [open win.tr w]
$ns_ namtrace [open simple.nam w]

$ns_ trace-all $tracefd
$ns_ namtrace-all-wireless $namtrace $val(x) $val(y)
set topo [new Topography]
$topo load_flatgrid $val(x) $val(y)
create-god $val(nn)

$ns_ node-config -adhocRouting $val(rp) \
		 -channelType $val(chan) \
		 -propType $val(prop) \
		 -phyType $val(netif) \
		 -macType $val(mac) \
		 -ifqType $val(ifq) \
		 -llType $val(ll) \
		 -antType $val(ant) \
		 -ifqLen $val(ifqlen) \
		 -topoInstance $topo \
		 -agentTrace ON \
		 -routerTrace ON \
		 -macTrace ON \
		 -movementTrace ON

for {set i 0} { $i < $val(nn) } { incr i } {
	set node_($i) [$ns_ node]
}

$node_(0) set X_ 5.0
$node_(0) set Y_ 5.0
$node_(0) set Z_ 0.0
$node_(1) set X_ 140.0
$node_(1) set Y_ 250.0
$node_(1) set Z_ 0.0
$node_(2) set X_ 460.0
$node_(2) set Y_ 230.0
$node_(2) set Z_ 0.0
$node_(3) set X_ 400.0
$node_(3) set Y_ 330.0
$node_(3) set Z_ 0.0
$node_(4) set X_ 60.0
$node_(4) set Y_ 30.0
$node_(4) set Z_ 0.0
$node_(5) set X_ 40.0
$node_(5) set Y_ 120.0
$node_(5) set Z_ 0.0
$node_(6) set X_ 450.0
$node_(6) set Y_ 370.0
$node_(6) set Z_ 0.0
$node_(7) set X_ 270.0
$node_(7) set Y_ 130.0
$node_(7) set Z_ 0.0
$node_(8) set X_ 190.0
$node_(8) set Y_ 230.0
$node_(8) set Z_ 0.0
$node_(9) set X_ 490.0
$node_(9) set Y_ 390.0
$node_(9) set Z_ 0.0
$node_(10) set X_ 250.0
$node_(10) set Y_ 250.0
$node_(10) set Z_ 0.0
$node_(11) set X_ 50.0
$node_(11) set Y_ 60.0
$node_(11) set Z_ 0.0
$node_(12) set X_ 260.0
$node_(12) set Y_ 120.0
$node_(12) set Z_ 0.0
$node_(13) set X_ 480.0
$node_(13) set Y_ 300.0
$node_(13) set Z_ 0.0
$node_(14) set X_ 460.0
$node_(14) set Y_ 330.0
$node_(14) set Z_ 0.0

$ns_ at 10.0 "$node_(0) setdest 250.0 250.0 3.0"
$ns_ at 110.0 "$node_(1) setdest 450.0 280.0 5.0"
$ns_ at 230.0 "$node_(2) setdest 480.0 250.0 5.0"
$ns_ at 260.0 "$node_(3) setdest 120.0 420.0 3.0"
$ns_ at 50.0 "$node_(4) setdest 540.0 120.0 4.0"
$ns_ at 100.0 "$node_(5) setdest 200.0 350.0 3.0"
$ns_ at 400.0 "$node_(6) setdest 340.0 330.0 5.0"
$ns_ at 350.0 "$node_(7) setdest 290.0 220.0 5.0"
$ns_ at 320.0 "$node_(8) setdest 260.0 120.0 3.0"
$ns_ at 150.0 "$node_(9) setdest 320.0 450.0 4.0"
$ns_ at 500.0 "$node_(10) setdest 460.0 530.0 3.0"
$ns_ at 310.0 "$node_(11) setdest 300.0 240.0 4.0"
$ns_ at 410.0 "$node_(12) setdest 220.0 350.0 5.0"
$ns_ at 510.0 "$node_(13) setdest 520.0 250.0 4.0"
$ns_ at 610.0 "$node_(14) setdest 230.0 420.0 5.0"

set tcp [new Agent/TCP]
$ns_ attach-agent $node_(0) $tcp
set sink [new Agent/TCPSink]
$ns_ attach-agent $node_(1) $sink
$ns_ connect $tcp $sink
$tcp set class_ 2
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns_ at 10.0 "$ftp start"

proc plotWindow {tcpSource file} {
	global ns_
	set time 0.01
	set now [$ns_ now]
	set cwnd [$tcpSource set cwdn_]
	puts $file "$now $cwdn"
	$ns_ at [expr $now+$time] "plotWindow $tcpSource $file"
}

$ns_ at 10.1 "plotWindow $tcp $windowVsTime2"

for { set i 0 } { $i < $val(nn) } { incr i } {
	$ns_ initial_node_pos $node_($i) 30
}

for { set i 0 } { $i < $val(nn) } { incr i } {
	$ns_ at $val(stop) "$node_($i) reset";
}

$ns_ at $val(stop) "$ns_ end-nam-wireless $val(stop)"
$ns_ at $val(stop) "stop"
$ns_ at 150.01 "puts \" end simulator \" ; $ns_ halt"

proc stop {} {
 global ns_ tracefd namtrace
 $ns_ flush-trace
 close $tracefd
 close $namtrace
}

$ns_ run

