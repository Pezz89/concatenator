# Concatenator

A C++ application for generating granular synthesis driven representations of
audio files based on audio database analysis.

This application is under development with the aim to explore the creative
potential of combining short-time audio analyses with granular synthesis, to
synthesize perceptually related representations of target audio files. Through
use of analysed databases of varying sizes, an output can be generated that
represents a mix of the spectral and temporal features of the original target
sound and the corpus of source sounds.

To achieve this, a technique known as "concatenative synthesis" is used. This
form of synthesis combines the ability to window and join small segments of
sound to create a new sound (a process known as granular synthesis), with audio
analysis techniques capable of describing a sound in order to differentiate it
from others. By analysing small segments in a target sound for their perceptual
characteristics (such as pitch, timbre and loudness), it is then possible to
compare these segments to a collection of source sounds to find perceptually
similar segments. From this, the most perceptually similar matches can be taken
and joined using granular synthesis techniques in order to achieve the final
result.

Note: This project is currently under development and is not ready for release.
This project is based on the pysound project developed to explore concatenative
synthesis in Python which can be found here:
https://github.com/Pezz89/pysound
This project's primary goal at present is to build on the performance of
Pysound through the higher efficiency of the C++ language and to address issues
with packaging and distribution encountered during the development of that
project. 
