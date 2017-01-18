package com.my.game.Entities;

import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.math.Vector2;

import java.util.Vector;

public abstract class Enemy extends Entity {

    //public int room;
    protected Sound deathSound;

    public abstract void getDamage(int dmg);
    public abstract void updatePosition(Vector2 neededPosition);
    public abstract void shoot(Vector<Bullet> bullets);
}
