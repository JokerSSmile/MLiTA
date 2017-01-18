package com.my.game.Entities;

import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.maps.MapObject;
import com.badlogic.gdx.maps.MapObjects;
import com.badlogic.gdx.maps.objects.RectangleMapObject;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector2;

import com.my.game.ResourceStorage.ResourceManager;

import java.util.Vector;

public class RandomTank extends Enemy{

    private enum headState{
        DOWN,
        DOWN_SHOOT,
        RIGHT,
        RIGHT_SHOOT,
        UP,
        UP_SHOOT,
        LEFT,
        LEFT_SHOOT
    }

    private static final float CHANGE_DIR_TIME = 3;
    public static final Vector2 BODY_SIZE = new Vector2(32, 32);
    private static final float TIME_BETWEEN_FRAMES = 0.15f;
    private static final float BASIC_SPEED = 2;
    private static final float TILEMAP_SCALE = 2.75f;
    private static final float TIME_BETWEEN_SHOOTS = 1f;
    private static final float DAMAGE_TAKE_TIME_PAUSE = 1;
    private static final float TIME_BETWEEN_FRAMES_DESTROY = 0.02f;

    private float stateTime;
    private float lastChangeDirTime;
    private float lastHitTime;
    private float lastShootTime;
    private float timeBetweenShoots;

    private Animation animation;
    private Animation walkUpAnimation;
    private Animation walkDownAnimation;
    private Animation walkLeftAnimation;
    private Animation walkRightAnimation;
    private Animation deathAnimation;

    private ResourceManager manager;

    private moveState randMoveState;
    private headState shootState = headState.DOWN;

    public RandomTank(ResourceManager resources, Vector2 startPos){
        this.position = startPos;
        this.manager = resources;
        this.texture = resources.getTexture(ResourceManager.randomTankTexture);
        stateTime = 0;
        lastChangeDirTime = 0;
        lastHitTime = 0;
        timeBetweenShoots = TIME_BETWEEN_SHOOTS;
        damage = 20;
        health = 45;
        //deathSound = resources.getSound(ResourceManager.enemyDies);

        rectangle = new Rectangle(position.x, position.y, BODY_SIZE.x, BODY_SIZE.y);

        randMoveState = moveState.values()[(int)(Math.random()*4 + 1)];

        createAnimations(resources);
        setAnimation();
    }

    private void createAnimations(ResourceManager resources){
        TextureRegion[][] frames = TextureRegion.split(texture, 32, 32);

        walkUpAnimation = new Animation(TIME_BETWEEN_FRAMES, frames[0][0]);
        walkRightAnimation = new Animation(TIME_BETWEEN_FRAMES, frames[0][1]);
        walkLeftAnimation = new Animation(TIME_BETWEEN_FRAMES, frames[0][2]);
        walkDownAnimation = new Animation(TIME_BETWEEN_FRAMES, frames[0][3]);

        Texture destroyTexture = resources.getTexture(ResourceManager.enemyDestroyTexture);
        TextureRegion[] deathFrames = com.my.game.ResourceStorage.Animation.getFramesArray1D(destroyTexture, 3, 4);
        deathAnimation = new Animation(TIME_BETWEEN_FRAMES_DESTROY, deathFrames);
    }

    private void setAnimation(){

        switch (randMoveState){
            case UP:
                animation = walkUpAnimation;
                break;
            case DOWN:
                animation = walkDownAnimation;
                break;
            case RIGHT:
                animation = walkRightAnimation;
                break;
            case LEFT:
                animation = walkLeftAnimation;
                break;
        }
    }

   /* @Override
    public void getDamage(int dmg) {
        health -= dmg;
    }*/

    @Override
    public void updatePosition(Vector2 neededPosition) {

    }

    @Override
    public void render(SpriteBatch batch) {

        if (liveState == aliveState.ALIVE) {
            batch.draw(animation.getKeyFrame(stateTime, true), position.x, position.y);
        }
        else {
            batch.draw(animation.getKeyFrame(stateTime, true), position.x, position.y);
        }
    }

    @Override
    public void update(float dt, MapObjects collidable) {

        isAlive = health > 0;

        stateTime += dt;

        if (stateTime > lastChangeDirTime + CHANGE_DIR_TIME){
            randMoveState = moveState.values()[(int)(Math.random()*4 + 1)];
            lastChangeDirTime = stateTime;

            setAnimation();
        }

        if (liveState == aliveState.ALIVE) {
            switch (randMoveState) {
                case UP:
                    position.y += BASIC_SPEED;
                    break;
                case DOWN:
                    position.y -= BASIC_SPEED;
                    break;
                case RIGHT:
                    position.x += BASIC_SPEED;
                    break;
                case LEFT:
                    position.x -= BASIC_SPEED;
                    break;
            }
        }

        if (!isAlive && liveState == aliveState.ALIVE){
            animation = deathAnimation;
            liveState = aliveState.DYING;
            stateTime = 0;
            //deathSound.play();
        }

        if (liveState == aliveState.DYING){
            if (deathAnimation.isAnimationFinished(stateTime)){
                liveState = aliveState.DEAD;
            }
        }

        rectangle.setPosition(position.x, position.y);

        checkCollision(collidable);

    }

    public void checkCollision(MapObjects collidable){
        boolean isCollides = false;
        for (MapObject wall : collidable){
            if (wall instanceof RectangleMapObject) {
                Rectangle rect = ((RectangleMapObject) wall).getRectangle();
                Rectangle randRect = new Rectangle(rectangle.getX(), rectangle.getY(),
                        rectangle.getWidth(), rectangle.getHeight() * 2);
                if (randRect.overlaps(new Rectangle(rect.getX() * TILEMAP_SCALE, rect.getY() * TILEMAP_SCALE,
                        rect.getWidth() * TILEMAP_SCALE, rect.getHeight() * TILEMAP_SCALE))){
                    isCollides = true;
                    break;
                }
            }
        }

        if (isCollides){
            switch (randMoveState){
                case UP:
                    position.y -= BASIC_SPEED * 2;
                    break;
                case DOWN:
                    position.y += BASIC_SPEED * 2;
                    break;
                case RIGHT:
                    position.x -= BASIC_SPEED * 2;
                    break;
                case LEFT:
                    position.x += BASIC_SPEED * 2;
                    break;
            }

            randMoveState = moveState.values()[(int)(Math.random()*4 + 1)];
            lastChangeDirTime = stateTime;
            setAnimation();
        }
    }

    public int getHealth(){
        return health;
    }

    public void getDamage(int dmg){
        if (stateTime > lastHitTime + DAMAGE_TAKE_TIME_PAUSE || lastHitTime == 0){
            Sound hurtSound = manager.getSound(ResourceManager.playerHurts);
            hurtSound.play();
            health -= dmg;
            lastHitTime = stateTime;
        }
    }

    public int getCurrentDamage(){
        return damage;
    }

    public void shoot(Vector<Bullet> bullets){

        Vector2 bulletVelocity = null;
        switch (randMoveState)
        {
            case UP:
                bulletVelocity = new Vector2(0, 0.5f);
                break;
            case DOWN:
                bulletVelocity = new Vector2(0, -0.5f);
                break;
            case RIGHT:
                bulletVelocity = new Vector2(0.5f, 0);
                break;
            case LEFT:
                bulletVelocity = new Vector2(-0.5f, 0);
                break;
        }


        if (bulletVelocity.x != 0f || bulletVelocity.y != 0f) {
            if (stateTime > lastShootTime + timeBetweenShoots || lastShootTime == 0) {
                bullets.add(new Bullet(manager, new Vector2(this.position.x + size.x / 2
                        , this.position.y + size.y), bulletVelocity, false));
                lastShootTime = stateTime;
            }
        }

        if (bulletVelocity.y > 0.8){
            shootState = stateTime > lastShootTime + timeBetweenShoots / 5 ? headState.UP : headState.UP_SHOOT;

        }
        else if (bulletVelocity.y < -0.8){
            shootState = stateTime > lastShootTime + timeBetweenShoots / 5 ? headState.DOWN : headState.DOWN_SHOOT;
        }
        else if (bulletVelocity.x > 0.5){
            shootState = stateTime > lastShootTime + timeBetweenShoots / 5 ? headState.RIGHT : headState.RIGHT_SHOOT;
        }
        else if (bulletVelocity.x < -0.5){
            shootState = stateTime > lastShootTime + timeBetweenShoots / 5 ? headState.LEFT : headState.LEFT_SHOOT;
        }
        else {
            shootState = stateTime > lastShootTime + timeBetweenShoots / 5 ? headState.DOWN : headState.DOWN_SHOOT;

        }
    }

    public void decreaseTimeBetweenShoots(float upgradeBonus){
        this.timeBetweenShoots -= upgradeBonus;
    }

    public void increaseDamage(float upgradeBonus){
        this.damage += upgradeBonus;
    }

    @Override
    public void dispose() {

    }

    @Override
    public Rectangle getRectangle() {
        return rectangle;
    }
}
