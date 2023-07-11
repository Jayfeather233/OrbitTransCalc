# OrbitTransCalc
Calculate deltaV for orbit transfer within a central body

---

This project is used to calculate how much deltaV you need to change your orbit within a central body. This idea comes from a game: [KSP](https://store.steampowered.com/app/220200/Kerbal_Space_Program/) and its realistic [mods](https://forum.kerbalspaceprogram.com/topic/190040-rp-1-realistic-progression-one-for-ksp-1123/). It only works for 2-body model with no inclination and using Hohmann Transfer.

---

Here is a simple example:

The deltaV calculated by my program from 200km to GEO. (I slightly changed my orbit's inclination because of enough fuel)

![i1](./img/img1.png)

![i2](./img/img2.png)

If not changing the inclination:

![i5](./img/img5.png)

![i6](./img/img6.png)

Here is the 'real' useage in game.

![i3](./img/img3.png)

![i4](./img/img4.png)

You can see there is a small difference, due to Principia (n-body mod) and the engine taking time to burn, so the result is not that accurate. But it can still give you a big image of how much dV is needed.