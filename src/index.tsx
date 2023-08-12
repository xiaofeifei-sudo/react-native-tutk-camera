import {
  requireNativeComponent,
  UIManager,
  Platform,
  type ViewStyle,
  NativeModules,
} from 'react-native';


const LINKING_ERROR =
  `The package 'react-native-tutk-camera' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';

type TutkCameraProps = {
  color: string;
  style: ViewStyle;

  videoWidth: number;

};

const ComponentName = 'TutkCameraView';

export const TutkCameraViewModule = NativeModules.TutkCameraViewManager;

export const TutkCameraView =
  UIManager.getViewManagerConfig(ComponentName) != null
    ? requireNativeComponent<TutkCameraProps>(ComponentName)
    : () => {
      throw new Error(LINKING_ERROR);
    };
