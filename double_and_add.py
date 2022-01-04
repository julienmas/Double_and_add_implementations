# P = (x1,y1), Q=(x2,y2)
# R = P+Q = (x3,y3)
# 
# The equation for all elliptic curves defined here is:
#       E : y^2 = x^3 + ax + b (mod p)
#    Domain parameter sets consist of:
#    o  p: the prime
#    o  a, b: parameters to the equation of the curve
#    o  x, y: the coordinates of the generator for the group, G
#    o  q: the order of the group formed by the generator G
#    o  h: the co-factor
#    o  z: the "twist" (for conversion into twisted curves)
#
# Domain Parameters for the 224-Bit Curve
#    Curve-ID: brainpoolP224r1
#    p = D7C134AA264366862A18302575D1D787B09F075797DA89F57EC8C0FF
#    A = 68A5E62CA9CE6C1C299803A6C1530B514E182AD8B0042A59CAD29F43
#    B = 2580F63CCFE44138870713B1A92369E33E2135D266DBB372386C400B
#    x = 0D9029AD2C7E5CF4340823B2A87DC68C9E4CE3174C1E6EFDEE12C07D
#    y = 58AA56F772C0726F24C6B89E4ECDAC24354B9E99CAA3F6D3761402CD
#    q = D7C134AA264366862A18302575D0FB98D116BC4B6DDEBCA3A5A7939F
#    z = 2DF271E14427A346910CF7A2E6CFA7B3F484E5C2CCE1C8B730E28B3F
#    h = 1

import math

class elliptic_curve:
    def __init__(self, p, A, B, ID=None):
        self.ID = ID
        self.p = p
        self.A = A
        self.B = B


class point_2d:
    def __init__(self, x, y, name=None):
        self.name = name
        self.x = x
        self.y  = y

    def opp(self):
        self.y = -y
    
    def print_coord(self):
        if self.name != None:
            print(self.name)
        print("x: ", hex(self.x))
        print("y: ", hex(self.y))

class point_3d:
    def __init__(self, x, y, z, name=None):
        self.name = name
        self.x = x
        self.y  = y
        self.z = z

    def opp(self):
        self.y = -y

    def print_coord(self):
        if self.name != None:
            print(self.name)
        print("x: ", self.x)
        print("y: ", self.y)
        print("z: ", self.z)

#les égalités r = a*u+b*v et r' = a*u'+b*v' sont des invariants de boucle
def ext_eucl_alg(a,b): #inversion modulaire grace à l'algo d'euclide étendu
    (r, u, v, rp, up, vp) = (a, 1, 0, b, 0, 1)

    while(rp != 0):
        q = r//rp 
        (r, u, v, rp, up, vp) = (rp, up, vp, r - q *rp, u - q*up, v - q*vp)

    return r, u, v


def add_aff(P,Q,c):
    #if P != Q and P != Q.opp():
    x1 = P.x
    y1 = P.y
    x2 = Q.x
    y2 = Q.y
    p = c.p

    num_l = (y1-y2)%p
    den_l = (x1-x2)%p
    r, inv_den_l, v = ext_eucl_alg(den_l, p)

    l = (num_l*inv_den_l)%p
    x3 = ((l*l)%p - x1 - x2)%p
    y3 = ((l*(x1-x3))%p - y1)%p

    R = point_2d(x3,y3)
    return R
    '''elif P == Q:
        return double_aff(P,c)
    else:
        return (-double_aff(P, c))%p'''


def double_aff(P,c): # P :point; c : elliptic curve
    x1 = P.x
    y1 = P.y
    A = c.A
    p = c.p

    num_l = (3*x1*x1 + A)%p
    den_l = (2*y1)%p
    r, inv_den_l, v = ext_eucl_alg(den_l, p)

    l = (num_l*inv_den_l)%p
    x3 = ((l*l)%p - 2*x1)%p
    y3 = ((l*(x1-x3))%p - y1)%p

    R = point_2d(x3,y3)
    return R


def add_proj(P,Q,c):
    x1 = P.x
    y1 = P.y
    z1 = P.z
    x2 = Q.x
    y2 = Q.y
    z2 = Q.z
    p = c.p

    a = (y2*z1)%p - (y1*z2)%p
    b = (x2*z1)%p - (x1*z2)%p
    b3 = (((b*b)%p)*b)%p
    d = (((((b*b)%p)*x1)%p)*z2)%p
    c = ((((a*a)%p) * ((z1*z2)%p))%p - b3 - (2*d)%p)%p
    
    x3 = (b*c)%p
    y3 = ((a*(d-c))%p - (((b3*y1)%p)*z2)%p)%p
    z3 = (((b3*z1)%p)*z2)%p

    R = point_3d(x3, y3, z3)
    return R


def double_proj(P,c):
    x1 = P.x
    y1 = P.y
    z1 = P.z
    p = c.p
    A = c.A

    a = ((A*(z1*z1)%p)%p + (3*((x1*x1)%p))%p)%p
    b = (y1*z1)%p
    c = (((x1*y1)%p)*b)%p
    d = ((a*a)%p - (8*c)%p)%p
    b3 = (((b*b)%p)*b)%p

    x3 = (2*b*d)%p
    y3 = ((a*(4*c-d))%p - (((8*y1*y1)%p)*((b*b)%p))%p)%p
    z3 = (8*b3)%p

    R = point_3d(x3, y3, z3)
    return R


p = 0xD7C134AA264366862A18302575D1D787B09F075797DA89F57EC8C0FF
# dec : 22721622932454352787552537995910928073340732145944992304435472941311
A = 0x68A5E62CA9CE6C1C299803A6C1530B514E182AD8B0042A59CAD29F43
#dec : 11020725272625742361946480833014344015343456918668456061589001510723
B = 0x2580F63CCFE44138870713B1A92369E33E2135D266DBB372386C400B
#dec : 3949606626053374030787926457695139766118442946052311411513528958987
x = 0x0D9029AD2C7E5CF4340823B2A87DC68C9E4CE3174C1E6EFDEE12C07D
#dec : 1428364927244201726431498207475486496993067267318520844137448783997
y = 0x58AA56F772C0726F24C6B89E4ECDAC24354B9E99CAA3F6D3761402CD
#dec : 9337555360448823227812410753177468631215558779020518084752618816205
z = 1

Q = point_2d(x, y, name="Q")
Q3 = point_3d(x, y, z)

brainpoolP224r1 = elliptic_curve(p, A, B)

print("Q*2 affine")
dQ = double_aff(Q, brainpoolP224r1)
dQ.print_coord()

print("Q*3 affine")
tQ = add_aff(dQ, Q, brainpoolP224r1)
tQ.print_coord()

print("Q*2 proj")
dQ3 = double_proj(Q3, brainpoolP224r1)
dQ3.print_coord()
#inv_dz3 =  ext_eucl_alg(dQ3.z, p)
inv_dz3 = pow(dQ3.z, p-2, p)

#print((dQ3.z * inv_dz3)%p)

print("en affine : ")
print("x: ", (dQ3.x*inv_dz3)%p)
print("y: ", (dQ3.y*inv_dz3)%p)

# print("Q*3 proj")
# tQ3 = add_proj(dQ3, Q3, brainpoolP224r1)
# tQ3.print_coord()
# tz3 = tQ3.z

# print("en affine : ")
# print("x: ", (tQ3.x*tz3)%p)
# print("y: ", (tQ3.y*tz3)%p)