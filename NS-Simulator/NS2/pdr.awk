BEGIN {
 rcvdSize = 0
 startTime = 400
 stopTime = 0
}

{
 event = $1
 time = $3
 node_id = $37
 pkt_size = $41
 level = $19

 if( level == "AGT" && event == "s" && pkt_size >= 512 ){
  if(time < startTime){
   startTime = time;
  }
 }
 
 if( level == "AGT" && event == "r" && pkt_size >= 512){
  if(time > stopTime){
   stopTime = time;
  }
  
  hdr_size = pkt_size % 12
  pkt_size -= hdr_size
  rcvdSize += pkt_size
}

END{
 printf("Average Throughput[kbps] = %.2f\t\tStart Time = %.2f Stop Time = %.2f\n",(rcvdSize/(stopTime-startTime))*(8/1000),startTime,stopTime);
}
