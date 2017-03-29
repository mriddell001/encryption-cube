Summary: Up to this point, I have determined that it is unnecessary to build a function that will automatically solve a cube. Due to the nature of encryption, a lock needs a key to open. No encryption should open a lock without a key. Therefore, at this point, my project completes the basic needs of an encryption software with a single key point missing, this format does not accept a key and open the lock.

Goals: Upon start up, perform one of two tasks. Either allow the user to select a text and generate a .cube file and a .key file or to select a .cube file and a .key file and convert the file back into text.

Changes: Now that this is moving out of the testing phase, testing resources will be removed and streamlined. It should no longer accept command line arguments and should randomly generate a number of transformations between 1-26 with a favoritism toward higher complexity.

Needs: A formula to deduce which transformations are acceptable given a previous string of transformations is needed. An example of this would be that a clockwise turn of the TOP face followed by a counter clockwise turn of the TOP face results in a net of no change.
