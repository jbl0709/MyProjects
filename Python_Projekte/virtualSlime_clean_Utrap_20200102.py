# -*- coding: utf-8 -*-
"""
Created on Wed Jan  1 12:13:58 2020

@author: Johannes
"""

import numpy as np
import matplotlib.pyplot as plt

from random import choice
from scipy import signal
from scipy import ndimage

def nannorm(X):
    Xmax, Xmin = np.nanmax(X), np.nanmin(X)
    return (X.copy()-Xmin)/(Xmax-Xmin)

def diffuse(X, sigma):
    X = ndimage.gaussian_filter(X, sigma=sigma) #, mode='wrap')
    return X

def plot(A, R, M, S):
    
    # A: attractant
    # A: attractant
    # A: attractant
    # A: attractant
    
    rgb = np.zeros((*A.shape, 3), dtype=np.uint8)
    
    R[np.isinf(R)] = np.nan
    By, Bx = np.where(np.isnan(R))
    My, Mx = np.where(M > 0)
    
    # repellent, attractant, slime
    rgb[:,:,0] = nannorm(R)*255
    rgb[:,:,1] = nannorm(A)*255
    rgb[:,:,2] = nannorm(S)*255
    
    # mold
    rgb[My,Mx,0:2] = 255

    # barrier
    rgb[By,Bx,:] = 255
    
    plt.imshow(rgb)
    
def get_candidates(B):
    
    ## from i to o
    
    K = np.asarray([[1, 1, 1], [1, 0, 1], [1, 1, 1]])
    
    S = signal.convolve2d(B != 0,K,mode='same') #, boundary='wrap')

    E = np.bitwise_and(B != 0, S < 7)
    D = np.bitwise_and(B == 0, S > 2)
    
    i, o = np.argwhere(E), np.argwhere(D)
    
    i = [(i[v,0], i[v,1]) for v in range(len(i))]
    o = [(o[v,0], o[v,1]) for v in range(len(o))]
    
    ci, co = choice(i), choice(o)
    
    return ci, co


### initial configuration

# define initial configurations for all matrices
    
# A: attractant
# R: repellent
# M: mold
# S: slime
    
def test():
    
    size = (100, 300)
    
    X, Y = np.meshgrid(np.arange(size[1]),np.arange(size[0]))

    
    A = np.zeros(size)
    
    # gradient
    A = X/np.max(X)

    R = np.zeros(size)
    
    # barrier / gradient(function, ---)
    
    R[20:80, 100:120] = np.inf
    
    M = np.zeros(size)
    
    M[45:55, 10:20] = 1
    
    # initial slime mold location
    
    S = np.zeros(size)
    
    return A, R, M, S


def utrap():
    
    size = (100, 300)
    
    X, Y = np.meshgrid(np.arange(size[1]),np.arange(size[0]))

    
    A = np.zeros(size)
    
    # gradient
    A = X/np.max(X)

    R = np.zeros(size)
    
    # barrier / gradient(function, ---)
    
    R[80:85, 190:240] = np.inf 
    R[15:20, 190:240] = np.inf
    R[15:85, 240:245] = np.inf
    
    
   # R[]
    
    M = np.zeros(size)
    
    M[45:55, 10:20] = 1
    
    # initial slime mold location
    
    S = np.zeros(size)
    
    return A, R, M, S



# A, R, M, S = test()
A, R, M, S = utrap()

#plot(A, R, M, S)

## p: Potencies, positive = repellent, negative = attractant
## larger values mean that the effect is stronger
pA = -1
pR = 1
#pM = -1
pS = 1

## inverse Temperatures b = 1/kT, always positive. A smaller value means that the particle is more likely to act stochastically
bA = 100  # attractant
bR = 0.01   # repellent
#bM = 100   # cohesion
bS = 0.01  # slime (repellent)

## parameters for slime creation
diffS = 0.5 # diffusion constant (how fast does the slime diffuse?)
prodS = 0.005 # production rate (how much slime is produced per time step)

N = 250000
n = 0

plt.figure()

while n < N:

    ## get candidate pixels ci: in the mold, co: adjencent to the mold (inner / outer)
    ci, co = get_candidates(M)
    
    ## calculate energy differences between ci and co
    
    dEA = pA*(A[co]-A[ci])
    dER = pR*(R[co]-R[ci])
    
    dES = pS*(S[co]-S[ci])
    
    
    p = np.min([1,np.exp(-bA*dEA)]) * np.min([1,np.exp(-bR*dER)]) * np.min([1,np.exp(-bS*dES)])
    
    if dEA + dER + dES <= 0:
        
        M[ci], M[co] = 0, 1
        n += 1
        
        # produce slime
        S = S + prodS*M
        
        # diffuse slime
        S = diffuse(S, diffS)

    elif np.random.rand() <= p:
        
        M[ci], M[co] = 0, 1
        n += 1    
        
         # produce slime
        S = S + prodS*M
        
        # diffuse slime
        S = diffuse(S, diffS)

        
        
    ### only for plotting (plot every 100th iteration)    
    if not np.mod(n,100):
        plot(abs(pA)*A, abs(pR)*R, M, abs(pS)*S)
        plt.xticks([], [])
        plt.yticks([], [])
        plt.axis('off')
        plt.pause(0.0001)
        plt.draw()
        plt.cla()
    