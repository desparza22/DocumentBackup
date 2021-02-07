# DocumentBackup
Run main.c to see the program restore information.  

The Function:
With a collection of separate chunks of information, which could take the form of a collection of documents or data centers for example, everything can be backed up collectively with minimal space requirements. 
This depends on the condition that the individual chunks of information, which would represent a single document or data center, would be individually corrupted. This means that the program does not work for a collection of documents that could be corrupted at the same time. 
It also depends on the assumption that, once a chunk of information is corrupted, the rest of the collection can be produced for the process of recovering the information that was corrupted.

The Process:
The program uses an error correction algorithm that is often used to detect a flipped bit in a chunk of bits. The general idea is to keep a bit representing the parity of the number of active bits in different sections of the chunk of bits. For example, one bit might track the overall parity, another might track the parity of every other bit, and yet another would track the parity of every other set of two bits. Collectively, these parity bits can be used to deduce which bit was corrupted. To take advantage of this algorithm, the program alternates the bits of information in the documents given to it. With 64 documents, if a document is corrupted, one bit in every 64 bits will be corrupted as well, which can be corrected with the method described.

Performace:
A collection of n bits, where n is a power of two, requires log(n) + 1 bits to detect a flipped bit. This means that a collection of n documents of equal length b bits will require b x (log(n) + 1) bits to encode. 

Next Steps:
One assumption made was that the documents are of equal length. It remains to be seen if there is a better method than simply extending all of the documents to the length of the largest document.
Another assumption was that the number of documents is a power of 2. The current program rounds performance upwards, so that a collection of 2^x + 1 documents will take up as much memory as a collection of 2^(x+1) documents. It may be possible to, instead, group the documents into groups of powers of 2, which would also allow for multiple documents to be corrupted, at the cost of increasing the memory required to back up the documents.
