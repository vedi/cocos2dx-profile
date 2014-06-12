package com.soomla.cocos2dx.profile;

import android.opengl.GLSurfaceView;
import com.soomla.cocos2dx.common.DomainHelper;
import com.soomla.profile.events.RewardGivenEvent;
import com.soomla.profile.events.UserProfileUpdatedEvent;
import com.soomla.profile.events.auth.*;
import com.soomla.profile.events.social.*;
import com.soomla.store.BusProvider;
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
                    parameters.put("method", "com.soomla.profile.events.auth.LoginFailedEvent");
                    parameters.put("errorDescription", loginFailedEvent.ErrorDescription);
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.auth.LoginFinishedEvent");
                    parameters.put("userProfile", loginFinishedEvent.UserProfile.toJSONObject());
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.auth.LoginStartedEvent");
                    parameters.put("provider", loginStartedEvent.Provider);
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.auth.LogoutFailedEvent");
                    parameters.put("errorDescription", logoutFailedEvent.ErrorDescription);
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.auth.LogoutFinishedEvent");
                    parameters.put("userProfile", logoutFinishedEvent.UserProfile.toJSONObject());
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.auth.LogoutStartedEvent");
                    parameters.put("provider", logoutStartedEvent.Provider);
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.social.GetContactsFailedEvent");
                    parameters.put("socialActionType", getContactsFailedEvent.SocialActionType);
                    parameters.put("errorDescription", getContactsFailedEvent.ErrorDescription);
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.social.GetContactsFinishedEvent");
                    parameters.put("socialActionType", getContactsFinishedEvent.SocialActionType);
                    parameters.put("contacts", DomainHelper.getInstance().getJsonObjectListFromDomains(getContactsFinishedEvent.Contacts));
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.social.GetContactsStartedEvent");
                    parameters.put("socialActionType", getContactsStartedEvent.SocialActionType);
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.social.SocialActionFailedEvent");
                    parameters.put("socialActionType", socialActionFailedEvent.SocialActionType);
                    parameters.put("errorDescription", socialActionFailedEvent.ErrorDescription);
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.social.SocialActionFinishedEvent");
                    parameters.put("socialActionType", socialActionFinishedEvent.SocialActionType);
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.social.SocialActionStartedEvent");
                    parameters.put("socialActionType", socialActionStartedEvent.SocialActionType);
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.auth.LoginCancelledEvent");
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.RewardGivenEvent");
                    parameters.put("reward", rewardGivenEvent.getReward().toJSONObject());
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
                    parameters.put("method", "com.soomla.profile.events.UserProfileUpdatedEvent");
                    parameters.put("userProfile", userProfileUpdatedEvent.UserProfile.toJSONObject());
                    ProfileNdkGlue.sendMessageWithParameters(parameters);
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
