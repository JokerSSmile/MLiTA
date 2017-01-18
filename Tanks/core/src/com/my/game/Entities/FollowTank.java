package com.my.game.Entities;

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
import com.my.game.Screen.PlayState;

import java.util.Vector;

public class FollowTank extends Enemy{

    private static final float TIME_BETWEEN_FRAMES = 0.1f;
    private static final float BASIC_SPEED = 2;
    private static final float TILEMAP_SCALE = PlayState.TILEMAP_SCALE;
    public static final Vector2 BODY_SIZE = new Vector2(32, 32);
    private static final float TIME_BETWEEN_FRAMES_DESTROY = 0.02f;

    private moveState followMoveState;

    private Texture headTexture;

    private float stateTime;

    private Animation animation;
    private Animation walkUpAnimation;
    private Animation walkDownAnimation;
    private Animation walkRightAnimation;
    private Animation walkLeftAnimation;
    private Animation deathAnimation;

    public FollowTank(ResourceManager resources, Vector2 startPos) {
        this.texture = resources.getTexture(ResourceManager.enemyTankTexture);
        this.position = startPos;
        damage = 15;
        health = 55;
        stateTime = 0;
        followMoveState = moveState.DOWN;
        rectangle = new Rectangle(startPos.x, startPos.y, 32, 32);
        velocity = new Vector2(0, 0);

        deathSound = resources.getSound(ResourceManager.enemyDies);

        createAnimations(resources);
        animation = walkUpAnimation;
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

    @Override
    public void render(SpriteBatch batch) {
        if (liveState == aliveState.ALIVE) {
            batch.draw(animation.getKeyFrame(stateTime, true), position.x, position.y, BODY_SIZE.x, BODY_SIZE.y);
        }
        else {
            batch.draw(animation.getKeyFrame(stateTime, true), position.x, position.y);
        }
    }

    @Override
    public void updatePosition(Vector2 playerPos){

        float diffX = playerPos.x - position.x;
        float diffY = playerPos.y - position.y;

        double angle = Math.atan2(diffY, diffX);
        velocity.x = (float)(BASIC_SPEED * Math.cos(angle));
        velocity.y = (float)(BASIC_SPEED * Math.sin(angle));


        if (velocity.y > 0.8){
            followMoveState = moveState.UP;
        }
        else if (velocity.y < -0.8){
            followMoveState = moveState.DOWN;
        }
        else if (velocity.x > 0.5){
            followMoveState = moveState.RIGHT;
        }
        else if (velocity.x < -0.5){
            followMoveState = moveState.LEFT;
        }
        else{
            followMoveState = moveState.NONE;
            this.velocity.x = 0;
            this.velocity.y = 0;
        }
    }

    @Override
    public void shoot(Vector<Bullet> bullets) {

    }

    private void setPosition(){
        position.x += velocity.x;
        position.y += velocity.y;
        rectangle.setPosition(this.position);
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
        switch (followMoveState){
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

    @Override
    public void update(float dt, MapObjects collidable) {

        isAlive = health > 0;

        stateTime += dt;

        if (isAlive) {

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


        if (!isAlive && liveState == aliveState.ALIVE){
            animation = deathAnimation;
            liveState = aliveState.DYING;
            stateTime = 0;
            deathSound.play();
        }

        if (liveState == aliveState.DYING){
            if (deathAnimation.isAnimationFinished(stateTime)){
                liveState = aliveState.DEAD;
            }
        }
    }

    @Override
    public void dispose() {

    }

    @Override
    public Rectangle getRectangle() {
        return new Rectangle(rectangle.getX(), rectangle.getY(),
                rectangle.getWidth(), rectangle.getHeight());
    }

    @Override
    public void getDamage(int dmg) {
        this.health -= dmg;
    }
}
