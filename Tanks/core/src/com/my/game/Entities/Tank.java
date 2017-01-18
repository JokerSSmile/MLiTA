package com.my.game.Entities;

import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.maps.MapObject;
import com.badlogic.gdx.maps.MapObjects;
import com.badlogic.gdx.maps.objects.RectangleMapObject;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector2;

import com.my.game.Screen.PlayState;
import com.my.game.ResourceStorage.ResourceManager;

import java.util.Vector;

public class Tank extends Entity{

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

    public static final Vector2 BODY_SIZE = new Vector2(32, 32);
    private static final int BASIC_VELOCITY = 5;
    private static final float TIME_BETWEEN_FRAMES = 0.1f;
    private static final float TILEMAP_SCALE = PlayState.TILEMAP_SCALE;
    private static final float TIME_BETWEEN_SHOOTS = 1f;
    private static final float DAMAGE_TAKE_TIME_PAUSE = 1;
    private static final int MAX_HEALTH = 150;

    private float velocityBonus;
    private float stateTime;
    private float lastHitTime;
    private float lastShootTime;
    private float timeBetweenShoots;

    private ResourceManager manager;

    private moveState playerMoveState;

    private Animation animation;
    private Animation walkUpAnimation;
    private Animation walkRightAnimation;
    private Animation walkLeftAnimation;
    private Animation walkDownAnimation;

    private headState shootState = headState.DOWN;

    public Tank (ResourceManager resources, Vector2 startPosition){

        this.manager = resources;
        this.texture = manager.getTexture(ResourceManager.tankTexture);

        playerMoveState = moveState.NONE;
        initPosition(startPosition);
        velocity = new Vector2();
        velocityBonus = 1;
        stateTime = 0;
        lastHitTime = 0;
        timeBetweenShoots = TIME_BETWEEN_SHOOTS;
        size = BODY_SIZE;
        damage = 20;
        health = 50;

        rectangle = new Rectangle(position.x, position.y, size.x, size.y);

        createAnimations();
        animation = walkUpAnimation;

    }

    public void initPosition(Vector2 pos){
        position = pos;
    }

    private void createAnimations(){
        TextureRegion[][] frames = TextureRegion.split(texture, 32, 32);

        walkUpAnimation = new Animation(TIME_BETWEEN_FRAMES, frames[0][0]);
        walkRightAnimation = new Animation(TIME_BETWEEN_FRAMES, frames[0][1]);
        walkLeftAnimation = new Animation(TIME_BETWEEN_FRAMES, frames[0][2]);
        walkDownAnimation = new Animation(TIME_BETWEEN_FRAMES, frames[0][3]);

        /*Texture destroyTexture = resources.getTexture(ResourceManager.enemyDestroyTexture);
        TextureRegion[] deathFrames = com.my.game.ResourceStorage.Animation.getFramesArray1D(destroyTexture, 3, 4);
        deathAnimation = new Animation(TIME_BETWEEN_FRAMES_DESTROY, deathFrames);*/
    }

    @Override
    public Rectangle getRectangle(){
        return rectangle;
    }

    public void inputHandler(Vector2 velocity){

        this.velocity.x = velocity.x * BASIC_VELOCITY * velocityBonus;
        this.velocity.y = velocity.y * BASIC_VELOCITY * velocityBonus;

        if (velocity.y > 0.8){
            playerMoveState = moveState.UP;
        }
        else if (velocity.y < -0.8){
            playerMoveState = moveState.DOWN;
        }
        else if (velocity.x > 0.5){
            playerMoveState = moveState.RIGHT;
        }
        else if (velocity.x < -0.5){
            playerMoveState = moveState.LEFT;
        }
        else{
            playerMoveState = moveState.NONE;
            this.velocity.x = 0;
            this.velocity.y = 0;
        }

    }

    private boolean isCollides(MapObjects collidable){
        for (MapObject wall : collidable) {
            Rectangle rect = ((RectangleMapObject) wall).getRectangle();
            if (getRectangle().overlaps(new Rectangle(rect.getX() * TILEMAP_SCALE, rect.getY() * TILEMAP_SCALE,
                    rect.getWidth() * TILEMAP_SCALE, rect.getHeight() * TILEMAP_SCALE))){
                return true;
            }
        }
        return false;
    }

    private void setAnimation(){
        switch (playerMoveState){
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
            case NONE:
                animation = walkUpAnimation;
                break;
        }
    }

    private void setPosition(){
        position.x += velocity.x;
        position.y += velocity.y;
        rectangle.setPosition(this.position);
    }

    public void setVelocity(Vector2 velocity){
        this.velocity = velocity;
    }

    public void update(float dt, MapObjects collidable){

        isAlive = health > 0;

        if (isAlive) {
            stateTime += dt;
            inputHandler(velocity);
            Vector2 oldPosition = new Vector2(rectangle.getX(), rectangle.getY());
            setPosition();
            rectangle.setPosition(position);
            if (isCollides(collidable)) {
                rectangle.setPosition(oldPosition);
                if (position.x != oldPosition.x && position.y != oldPosition.y) {
                    rectangle.setPosition(oldPosition.x, position.y);
                    if (isCollides(collidable)) {
                        rectangle.setPosition(position.x, oldPosition.y);
                        if (isCollides(collidable)) {
                            rectangle.setPosition(oldPosition);
                        }
                    }
                }
            }

            position.x = rectangle.getX();
            position.y = rectangle.getY();
            setAnimation();
        }
    }

    @Override
    public void render(SpriteBatch batch){
        if (isAlive) {
            batch.draw(animation.getKeyFrame(stateTime, true), rectangle.getX(), rectangle.getY(),
                    BODY_SIZE.x, BODY_SIZE.y);
        }
        else{
            batch.draw(animation.getKeyFrame(stateTime, true), rectangle.getX(), rectangle.getY(),
                    BODY_SIZE.x, BODY_SIZE.y);
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

    public void shoot(Vector<Bullet> bullets, Vector2 bulletVelocity){
        if (bulletVelocity.x != 0f && bulletVelocity.y != 0f) {
            if (stateTime > lastShootTime + timeBetweenShoots || lastShootTime == 0) {
                bullets.add(new Bullet(manager, new Vector2(this.position.x + size.x / 2
                        , this.position.y + size.y), bulletVelocity, true));
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

    public void increaseHealth(int upgradeBonus){
        if (health < MAX_HEALTH) {
            this.health += upgradeBonus;
        }
    }

    public void increaseSpeed(float upgradeBonus){
        this.velocityBonus += upgradeBonus;
    }

    public void decreaseTimeBetweenShoots(float upgradeBonus){
        this.timeBetweenShoots -= upgradeBonus;
    }

    public void increaseDamage(float upgradeBonus){
        this.damage += upgradeBonus;
    }

    @Override
    public void dispose(){

    }
}