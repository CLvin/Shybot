import numpy as np
import cv2

#import serial

#from matplotlib import pyplot as plt

#ser = serial.Serial('/dev/ttyACM0', 9600)
cap = cv2.VideoCapture(0)

# Capture frame-by-frame
ret, frame = cap.read()
# Our operations on the frame come here
gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)


# Display the resulting frame
#cv2.imshow('input', gray);
#cv2.imwrite('testing.png',gray)

#Blur image to blend but keep edges sharp
blurred = cv2.bilateralFilter(gray,5,55,25)
#cv2.imwrite('testingFIL.png',blurred)
#cv2.imshow('input', blurred);

#print blurred.shape
#print blurred.size


#EQUALIZE PICTURE
equ = cv2.equalizeHist(blurred)
res = np.hstack((blurred,equ)) #stacking images side-by-side
#cv2.imwrite('res.png',res)


#Gradient testing
laplacian = cv2.Laplacian(blurred,cv2.CV_64F)
laplacian2 = cv2.Laplacian(equ,cv2.CV_64F)


#cv2.imshow('input', equ);
#cv2.imshow('input2', laplacian2);


#POI
blurred = laplacian2;

Xmax = np.size(blurred, 0)
Ymax = np.size(blurred, 1)

print Xmax
print Ymax

LL = blurred[:, 0:Ymax/5]
L = blurred[:, (Ymax/5):(2*Ymax/5)]
M = blurred[:, (2*Ymax/5):(3*Ymax/5)]
R = blurred[:, (3*Ymax/5):(4*Ymax/5)]
RR = blurred[:, (4*Ymax/5):(5*Ymax/5)]

mLL = equ[:, 0:Ymax/5]
mL = equ[:, (Ymax/5):(2*Ymax/5)]
mM = equ[:, (2*Ymax/5):(3*Ymax/5)]
mR = equ[:, (3*Ymax/5):(4*Ymax/5)]
mRR = equ[:, (4*Ymax/5):(5*Ymax/5)]


#for vertical separation
TLL = blurred[(2*Xmax/3):(3*Xmax/3) , 0:Ymax/5]
TL = blurred[(2*Xmax/3):(3*Xmax/3) , (Ymax/5):(2*Ymax/5)]
TM = blurred[(2*Xmax/3):(3*Xmax/3) , (2*Ymax/5):(3*Ymax/5)]
TR = blurred[(2*Xmax/3):(3*Xmax/3), (3*Ymax/5):(4*Ymax/5)]
TRR = blurred[(2*Xmax/3):(3*Xmax/3), (4*Ymax/5):(5*Ymax/5)]

MLL = blurred[(1*Xmax/3):(2*Xmax/3) , 0:Ymax/5]
ML = blurred[(1*Xmax/3):(2*Xmax/3) , (Ymax/5):(2*Ymax/5)]
MM = blurred[(1*Xmax/3):(2*Xmax/3) , (2*Ymax/5):(3*Ymax/5)]
MR = blurred[(1*Xmax/3):(2*Xmax/3), (3*Ymax/5):(4*Ymax/5)]
MRR = blurred[(1*Xmax/3):(2*Xmax/3), (4*Ymax/5):(5*Ymax/5)]

BLL = blurred[0:(1*Xmax/3) , 0:Ymax/5]
BL = blurred[0:(1*Xmax/3) , (Ymax/5):(2*Ymax/5)]
BM = blurred[0:(1*Xmax/3) , (2*Ymax/5):(3*Ymax/5)]
BR = blurred[0:(1*Xmax/3), (3*Ymax/5):(4*Ymax/5)]
BRR = blurred[0:(1*Xmax/3), (4*Ymax/5):(5*Ymax/5)]
#

def whichLocation(M):
    gradM = np.gradient(M);
    gradM = np.array(gradM);
    GRAD = np.sqrt(np.add(np.square(gradM[1,:,:]), np.square(gradM[0,:,:])));

    a = [np.mean(GRAD), np.mean(M)]
    return a;



vLL = whichLocation(LL);
vL = whichLocation(L);
vM = whichLocation(M);
vR = whichLocation(R);
vRR =whichLocation(RR);

mLL = whichLocation(mLL);
mL = whichLocation(mL);
mM = whichLocation(mM);
mR = whichLocation(mR);
mRR =whichLocation(mRR);


varr = [vLL[0], vL[0], vM[0], vR[0], vRR[0]];
VARR = [vLL[1], vL[1], vM[1], vR[1], vRR[1]];

mvarr = [mLL[0], mL[0], mM[0], mR[0], mRR[0]];
MVARR = [mLL[1], mL[1], mM[1], mR[1], mRR[1]];

#Debugging purposes--------------
#print varr
print np.argsort(varr)
#print mvarr
print np.argsort(mvarr)
#print VARR
#print MVARR
print np.argsort(VARR)
print np.argsort(MVARR)


#OUTPUT AREA

def toRobot(A, B, C, D):
    Asorted = np.argsort(A);
    Bsorted = np.argsort(B);
    Csorted = np.argsort(C);
    Dsorted = np.argsort(D);

    if Bsorted[1] == Asorted[3]:
        return Bsorted[1];
    else:
        return Bsorted[2];

OUTPUT = toRobot(varr, mvarr, VARR, MVARR);

print OUTPUT;

#ser.write(OUTPUT);

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
