Phase 2: The Skeleton (Days 3–4)

This is about getting the program to "listen" without crashing.

    Task 2.1: Create the Socket. Write the logic to open a socket using socket(AF_PACKET, SOCK_RAW, ...) or socket(AF_INET, SOCK_RAW, ...).

    Task 2.2: The "Infinite Loop." Implement a while(1) loop that uses the recvfrom() function to pull raw bytes off the wire.

    Task 2.3: Buffer Management. Create a memory buffer (an array of unsigned char) to hold the incoming packets.

Phase 3: Parsing the Headers (Days 5–6)

This is where the "Involve Me" OSI model learning happens. You are going to "carve" the data.

    Task 3.1: Extract the IP Header. Cast your raw buffer into an iphdr struct.

    Task 3.2: Print the Source/Destination. Extract the IP addresses from the header and print them to the console.

    Task 3.3: Identify the Protocol. Look at the "Protocol" field in the IP header to determine if the packet is TCP, UDP, or ICMP.

Phase 4: Refinement & Logging (Day 7)

    Task 4.1: Hex Dump. Write a small helper function to print the "payload" of the packet in Hexadecimal format (just like you see in Wireshark).

    Task 4.2: Error Handling. Add checks to ensure the socket opens correctly and the packet size is valid.

    Task 4.3: Document for LinkedIn. Take a screenshot of your terminal showing your C program successfully "sniffing" a ping request (ICMP).
