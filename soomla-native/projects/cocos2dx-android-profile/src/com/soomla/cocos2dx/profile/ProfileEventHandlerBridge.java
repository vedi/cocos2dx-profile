package com.soomla.cocos2dx.profile;

import android.opengl.GLSurfaceView;
import com.soomla.BusProvider;
import com.soomla.cocos2dx.common.DomainHelper;
import com.soomla.cocos2dx.common.NdkGlue;
import com.soomla.events.RewardGivenEvent;
import com.soomla.profile.events.UserProfileUpdatedEvent;
import com.soomla.profile.events.auth.*;
import com.soomla.profile.events.social.*;
import com.squareup.otto.Subscribe;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * This bridge is used to populate events from the store to cocos2dx (through JNI).
 */
public class ProfileEventHandlerBridge {

    private GLSurfaceView mGLThread;

    public ProfileEventHandlerBridge() {
        BusProvider.getInstance().register(this);
    }

    @Subscribe
    public void onLoginFailedEvent(final LoginFailedEvent loginFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGIN_FAILED);
                    parameters.put("errorDescription", loginFailedEvent.ErrorDescription);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onLoginFinishedEvent(final LoginFinishedEvent loginFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGIN_FINISHED);
                    parameters.put("userProfile", loginFinishedEvent.UserProfile.toJSONObject());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onLoginStartedEvent(final LoginStartedEvent loginStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGIN_STARTED);
                    parameters.put("provider", loginStartedEvent.Provider);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onLogoutFailedEvent(final LogoutFailedEvent logoutFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGOUT_FAILED);
                    parameters.put("errorDescription", logoutFailedEvent.ErrorDescription);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onLogoutFinishedEvent(final LogoutFinishedEvent logoutFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGOUT_FINISHED);
                    parameters.put("userProfile", logoutFinishedEvent.UserProfile.toJSONObject());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onLogoutStartedEvent(final LogoutStartedEvent logoutStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_AUTH_LOGOUT_STARTED);
                    parameters.put("provider", logoutStartedEvent.Provider);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGetContactsFailedEvent(final GetContactsFailedEvent getContactsFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_CONTACTS_FAILED);
                    parameters.put("socialActionType", getContactsFailedEvent.SocialActionType);
                    parameters.put("errorDescription", getContactsFailedEvent.ErrorDescription);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGetContactsFinishedEvent(final GetContactsFinishedEvent getContactsFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_CONTACTS_FINISHED);
                    parameters.put("socialActionType", getContactsFinishedEvent.SocialActionType);
                    parameters.put("contacts", DomainHelper.getInstance().getJsonObjectListFromDomains(getContactsFinishedEvent.Contacts));
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGetContactsStartedEvent(final GetContactsStartedEvent getContactsStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_GET_CONTACTS_STARTED);
                    parameters.put("socialActionType", getContactsStartedEvent.SocialActionType);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onSocialActionFailedEvent(final SocialActionFailedEvent socialActionFailedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_SOCIAL_ACTION_FAILED);
                    parameters.put("socialActionType", socialActionFailedEvent.SocialActionType);
                    parameters.put("errorDescription", socialActionFailedEvent.ErrorDescription);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onSocialActionFinishedEvent(final SocialActionFinishedEvent socialActionFinishedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_SOCIAL_ACTION_FINISHED);
                    parameters.put("socialActionType", socialActionFinishedEvent.SocialActionType);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onSocialActionStartedEvent(final SocialActionStartedEvent socialActionStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_SOCIAL_ACTION_STARTED);
                    parameters.put("socialActionType", socialActionStartedEvent.SocialActionType);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @SuppressWarnings("UnusedParameters")
    @Subscribe
    public void onLoginCancelledEvent(final LoginCancelledEvent loginCancelledEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_LOGIN_CANCELLED);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onRewardGivenEvent(final RewardGivenEvent rewardGivenEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_REWARD_GIVEN);
                    parameters.put("reward", rewardGivenEvent.Reward.toJSONObject());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onUserProfileUpdatedEvent(final UserProfileUpdatedEvent userProfileUpdatedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", ProfileConsts.EVENT_USER_PROFILE_UPDATED);
                    parameters.put("userProfile", userProfileUpdatedEvent.UserProfile.toJSONObject());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    public void setGlSurfaceView(GLSurfaceView glSurfaceView) {
        this.mGLThread = glSurfaceView;
    }
}
