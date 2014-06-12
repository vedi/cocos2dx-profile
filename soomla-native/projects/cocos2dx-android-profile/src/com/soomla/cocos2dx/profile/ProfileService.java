package com.soomla.cocos2dx.profile;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import com.soomla.cocos2dx.common.DomainFactory;
import com.soomla.profile.domain.UserProfile;
import com.soomla.profile.domain.rewards.BadgeReward;
import com.soomla.profile.domain.rewards.RandomReward;
import com.soomla.profile.domain.rewards.SequenceReward;
import com.soomla.profile.domain.rewards.VirtualItemReward;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.json.JSONException;
import org.json.JSONObject;

import java.lang.ref.WeakReference;

/**
 * @author vedi
 *         date 6/10/14
 *         time 11:08 AM
 */
public class ProfileService {

    private static ProfileService INSTANCE = null;

    private static WeakReference<GLSurfaceView> glSurfaceViewRef = new WeakReference<GLSurfaceView>(null);
    private boolean inited = false;

    public static ProfileService getInstance() {
        if (INSTANCE == null) {
            synchronized (ProfileService.class) {
                if (INSTANCE == null) {
                    INSTANCE = new ProfileService();
                }
            }
        }
        return INSTANCE;
    }

    @SuppressWarnings("FieldCanBeLocal")
    private ProfileEventHandlerBridge profileEventHandlerBridge;

    public ProfileService() {
        profileEventHandlerBridge = new ProfileEventHandlerBridge();
        DomainFactory.getInstance().registerCreator(ProfileJsonConsts.JSON_JSON_TYPE_BADGE, new DomainFactory.Creator<BadgeReward>() {
            @Override
            public BadgeReward create(JSONObject jsonObject) {
                try {
                    return new BadgeReward(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
        DomainFactory.getInstance().registerCreator(ProfileJsonConsts.JSON_JSON_TYPE_RANDOM, new DomainFactory.Creator<RandomReward>() {
            @Override
            public RandomReward create(JSONObject jsonObject) {
                try {
                    return new RandomReward(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
        DomainFactory.getInstance().registerCreator(ProfileJsonConsts.JSON_JSON_TYPE_SEQUENCE, new DomainFactory.Creator<SequenceReward>() {
            @Override
            public SequenceReward create(JSONObject jsonObject) {
                try {
                    return new SequenceReward(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
        DomainFactory.getInstance().registerCreator(ProfileJsonConsts.JSON_JSON_TYPE_ITEM, new DomainFactory.Creator<VirtualItemReward>() {
            @Override
            public VirtualItemReward create(JSONObject jsonObject) {
                try {
                    return new VirtualItemReward(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
        DomainFactory.getInstance().registerCreator(ProfileJsonConsts.JSON_JSON_TYPE_USER_PROFILE, new DomainFactory.Creator<UserProfile>() {
            @Override
            public UserProfile create(JSONObject jsonObject) {
                try {
                    return new UserProfile(jsonObject);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    public void init() {
        final GLSurfaceView glSurfaceView = glSurfaceViewRef.get();
        if (glSurfaceView != null) {
            profileEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        }

        inited = true;
    }

    public void setActivity(Activity activity) {
        ProfileNdkGlue.setActivity(activity);
    }

    public void setGlSurfaceView(Cocos2dxGLSurfaceView glSurfaceView) {
        if (inited) {
            profileEventHandlerBridge.setGlSurfaceView(glSurfaceView);
        } else {
            glSurfaceViewRef = new WeakReference<GLSurfaceView>(glSurfaceView);
        }
    }
}
