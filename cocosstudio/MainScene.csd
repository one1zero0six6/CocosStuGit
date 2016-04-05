<GameFile>
  <PropertyGroup Name="MainScene" Type="Scene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="21" Speed="1.0000">
        <Timeline ActionTag="1008763850" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="PlistSubImage" Path="cuber01.png" Plist="scene101.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="3" Tween="False">
            <TextureFile Type="PlistSubImage" Path="cuber02.png" Plist="scene101.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="6" Tween="False">
            <TextureFile Type="PlistSubImage" Path="cuber03.png" Plist="scene101.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="9" Tween="False">
            <TextureFile Type="PlistSubImage" Path="cuber04.png" Plist="scene101.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="12" Tween="False">
            <TextureFile Type="PlistSubImage" Path="cuber05.png" Plist="scene101.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="15" Tween="False">
            <TextureFile Type="PlistSubImage" Path="cuber06.png" Plist="scene101.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="18" Tween="False">
            <TextureFile Type="PlistSubImage" Path="cuber07.png" Plist="scene101.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="21" Tween="False">
            <TextureFile Type="PlistSubImage" Path="cuber08.png" Plist="scene101.plist" />
          </TextureFrame>
        </Timeline>
      </Animation>
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="1280.0000" Y="720.0000" />
        <Children>
          <AbstractNodeData Name="s101bgimg_1" ActionTag="1535818553" Tag="7" IconVisible="False" LeftMargin="0.9999" RightMargin="-0.9999" TopMargin="-2.8739" BottomMargin="2.8739" ctype="SpriteObjectData">
            <Size X="1280.0000" Y="720.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="640.9999" Y="362.8739" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5008" Y="0.5040" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="PlistSubImage" Path="s101bgimg.png" Plist="scene101bg.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Text101" ActionTag="-1208987007" CallBackType="Touch" Tag="11" IconVisible="False" LeftMargin="593.5000" RightMargin="573.5000" TopMargin="17.0000" BottomMargin="667.0000" FontSize="32" LabelText="Scene 101" OutlineEnabled="True" ShadowOffsetX="3.0000" ShadowOffsetY="-3.0000" ShadowEnabled="True" ctype="TextObjectData">
            <Size X="113.0000" Y="36.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="650.0000" Y="685.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="75" G="113" B="237" />
            <PrePosition X="0.5078" Y="0.9514" />
            <PreSize X="0.0883" Y="0.0500" />
            <FontResource Type="Normal" Path="Marker Felt.ttf" Plist="" />
            <OutlineColor A="255" R="0" G="11" B="139" />
            <ShadowColor A="255" R="26" G="26" B="26" />
          </AbstractNodeData>
          <AbstractNodeData Name="BMFont" ActionTag="-1814601833" Tag="9" IconVisible="False" LeftMargin="524.5000" RightMargin="504.5000" TopMargin="72.5005" BottomMargin="598.4995" LabelText="3D遊戲程式設計" ctype="TextBMFontObjectData">
            <Size X="251.0000" Y="49.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="650.0000" Y="622.9995" />
            <Scale ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5078" Y="0.8653" />
            <PreSize X="0.1961" Y="0.0681" />
            <LabelBMFontFile_CNB Type="Normal" Path="hansans48.fnt" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Gcuber" ActionTag="1652754442" Tag="12" IconVisible="False" LeftMargin="909.5000" RightMargin="129.5000" TopMargin="290.0000" BottomMargin="220.0000" ctype="SpriteObjectData">
            <Size X="241.0000" Y="210.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1030.0000" Y="325.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.8047" Y="0.4514" />
            <PreSize X="0.1883" Y="0.2917" />
            <FileData Type="PlistSubImage" Path="cuber01.png" Plist="scene101.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="CuberBtn" ActionTag="1110528250" Tag="7" IconVisible="False" LeftMargin="1142.0000" RightMargin="42.0000" TopMargin="46.5000" BottomMargin="586.5000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="66" Scale9Height="65" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="96.0000" Y="87.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1190.0000" Y="630.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9297" Y="0.8750" />
            <PreSize X="0.0750" Y="0.1208" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="PlistSubImage" Path="cuberbtn3.png" Plist="scene101bg.plist" />
            <PressedFileData Type="PlistSubImage" Path="cuberbtn2.png" Plist="scene101bg.plist" />
            <NormalFileData Type="PlistSubImage" Path="cuberbtn1.png" Plist="scene101bg.plist" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="CheckBox_1" ActionTag="-1137394645" Tag="8" IconVisible="False" LeftMargin="99.0000" RightMargin="1149.0000" TopMargin="84.0000" BottomMargin="604.0000" TouchEnable="True" CheckedState="True" ctype="CheckBoxObjectData">
            <Size X="32.0000" Y="32.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="115.0000" Y="620.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0898" Y="0.8611" />
            <PreSize X="0.0250" Y="0.0444" />
            <NormalBackFileData Type="PlistSubImage" Path="checkbox.png" Plist="scene101.plist" />
            <PressedBackFileData Type="PlistSubImage" Path="checkboxon.png" Plist="scene101.plist" />
            <DisableBackFileData Type="PlistSubImage" Path="checkbox.png" Plist="scene101.plist" />
            <NodeNormalFileData Type="PlistSubImage" Path="checkon.png" Plist="scene101.plist" />
            <NodeDisableFileData Type="PlistSubImage" Path="checkoff.png" Plist="scene101.plist" />
          </AbstractNodeData>
          <AbstractNodeData Name="LoadingBar_1" ActionTag="1740485087" Tag="9" IconVisible="False" LeftMargin="100.0000" RightMargin="1050.0000" TopMargin="41.5000" BottomMargin="661.5000" ProgressInfo="100" ctype="LoadingBarObjectData">
            <Size X="130.0000" Y="17.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="165.0000" Y="670.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1289" Y="0.9306" />
            <PreSize X="0.1016" Y="0.0236" />
            <ImageFileData Type="PlistSubImage" Path="loadingbar.png" Plist="scene101.plist" />
          </AbstractNodeData>
          <AbstractNodeData Name="Slider_1" ActionTag="-2085853825" Tag="10" IconVisible="False" LeftMargin="525.0000" RightMargin="505.0000" TopMargin="143.5000" BottomMargin="563.5000" TouchEnable="True" PercentInfo="50" ctype="SliderObjectData">
            <Size X="250.0000" Y="13.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="650.0000" Y="570.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5078" Y="0.7917" />
            <PreSize X="0.1953" Y="0.0181" />
            <BackGroundData Type="PlistSubImage" Path="sliderTrack.png" Plist="scene101.plist" />
            <ProgressBarData Type="PlistSubImage" Path="sliderProgress.png" Plist="scene101.plist" />
            <BallNormalData Type="PlistSubImage" Path="sliderballnormal.png" Plist="scene101.plist" />
            <BallPressedData Type="PlistSubImage" Path="sliderballpressed.png" Plist="scene101.plist" />
            <BallDisabledData Type="Default" Path="Default/SliderNode_Disable.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Sprite_1" ActionTag="1008763850" Tag="11" IconVisible="False" LeftMargin="519.5000" RightMargin="519.5000" TopMargin="290.0000" BottomMargin="220.0000" ctype="SpriteObjectData">
            <Size X="241.0000" Y="210.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="640.0000" Y="325.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.4514" />
            <PreSize X="0.0359" Y="0.0639" />
            <FileData Type="PlistSubImage" Path="cuber01.png" Plist="scene101.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>