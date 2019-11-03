function varargout = one(varargin)
% ONE MATLAB code for one.fig
%      ONE, by itself, creates a new ONE or raises the existing
%      singleton*.
%
%      H = ONE returns the handle to a new ONE or the handle to
%      the existing singleton*.
%
%      ONE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in ONE.M with the given input arguments.
%
%      ONE('Property','Value',...) creates a new ONE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before one_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to one_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help one

% Last Modified by GUIDE v2.5 19-Oct-2019 11:04:27

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @one_OpeningFcn, ...
                   'gui_OutputFcn',  @one_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before one is made visible.
function one_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to one (see VARARGIN)

% Choose default command line output for one
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

%初始化 开始 撤销 保存按钮不可点击
set(handles.startButton,'enable','off');
set(handles.undoButton,'enable','off');
set(handles.saveButton,'enable','off');

%Kirsch算子只能取最大
str=get(handles.operatorSelect,'String');
val=get(handles.operatorSelect,'Value');
if strcmp(str(val),'Kirsch算子')
    set(handles.optionSelect,'String',{'取最大'});
end
if strcmp(str(val),'Sobel算子')
    set(handles.optionSelect,'String',{'取最大';'取和'});
end

% UIWAIT makes one wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = one_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in startButton.
function startButton_Callback(hObject, eventdata, handles)
% hObject    handle to startButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%获取Operator和Option
operator_list=get(handles.operatorSelect,'String');
operator_val=get(handles.operatorSelect,'Value');
operator_name=operator_list{operator_val};

option_list=get(handles.optionSelect,'String');
option_val=get(handles.optionSelect,'Value');
option_name=option_list{option_val};



    global S;   %全局变量S保存着初始图像
    oldImage=imread(S);
    [high,width] = size(oldImage);   % 获得图像的高度和宽度        
    T = double(oldImage);       
    newImage = oldImage;
if strcmp(operator_name,'Sobel算子')  %Sobel边缘检测
    if strcmp(option_name,'取和')
        for i = 2:high - 1   
            for j = 2:width - 1
                Tx = (T(i-1,j+1) + 2*T(i,j+1) + T(i+1,j+1)) - (T(i-1,j-1) + 2*T(i,j-1) + T(i+1,j-1));
                Ty = (T(i+1,j-1) + 2*T(i+1,j) + T(i+1,j+1)) - (T(i-1,j-1) + 2*T(i-1,j) + T(i-1,j+1));
                newImage(i,j) = abs(Tx) + abs(Ty); 
            end
        end  
        set(handles.imageSolved,'HandleVisibility','ON');
        axes(handles.imageSolved);
        imshow(im2uint8(newImage));
    else
        for i = 2:high - 1   
            for j = 2:width - 1
                Tx = (T(i-1,j+1) + 2*T(i,j+1) + T(i+1,j+1)) - (T(i-1,j-1) + 2*T(i,j-1) + T(i+1,j-1));
                Ty = (T(i+1,j-1) + 2*T(i+1,j) + T(i+1,j+1)) - (T(i-1,j-1) + 2*T(i-1,j) + T(i-1,j+1));
                newImage(i,j) = max(abs(Tx),abs(Ty)); 
            end
        end   
        set(handles.imageSolved,'HandleVisibility','ON');
        axes(handles.imageSolved);
        imshow(im2uint8(newImage));
    end
else    %Kirsch边缘检测
    H1 = [-5 3 3;-5 0 3;-5 3 3];
    H2 = [3 3 3;-5 0 3;-5 -5 3];
    H3 = [3 3 3;3 0 3;-5 -5 -5];
    H4 = [3 3 3;3 0 -5;3 -5 -5];
    H5 = [3 3 -5;3 0 -5;3 3 -5];
    H6 = [3 -5 -5;3 0 -5;3 3 3];
    H7 = [-5 -5 -5;3 0 3;3 3 3];
    H8 = [-5 -5 3;-5 0 3;3 3 3];
    for i = 2:high - 1   %sobel边缘检测
            for j = 2:width - 1
                h1 = H1(1,1)*T(i-1,j-1) + H1(1,2)*T(i-1,j) + H1(1,3)*T(i-1,j+1) + H1(2,1)*T(i,j-1) + H1(2,2)*T(i,j) + H1(2,3)*T(i,j+1) + H1(3,1)*T(i+1,j) + H1(3,2)*T(i+1,j)+H1(3,3)*T(i+1,j+1);
                h2 = H2(1,1)*T(i-1,j-1) + H2(1,2)*T(i-1,j) + H2(1,3)*T(i-1,j+1) + H2(2,1)*T(i,j-1) + H2(2,2)*T(i,j) + H2(2,3)*T(i,j+1) + H2(3,1)*T(i+1,j) + H2(3,2)*T(i+1,j)+H2(3,3)*T(i+1,j+1);
                h3 = H3(1,1)*T(i-1,j-1) + H3(1,2)*T(i-1,j) + H3(1,3)*T(i-1,j+1) + H3(2,1)*T(i,j-1) + H3(2,2)*T(i,j) + H3(2,3)*T(i,j+1) + H3(3,1)*T(i+1,j) + H3(3,2)*T(i+1,j)+H3(3,3)*T(i+1,j+1);
                h4 = H4(1,1)*T(i-1,j-1) + H4(1,2)*T(i-1,j) + H4(1,3)*T(i-1,j+1) + H4(2,1)*T(i,j-1) + H4(2,2)*T(i,j) + H4(2,3)*T(i,j+1) + H4(3,1)*T(i+1,j) + H4(3,2)*T(i+1,j)+H4(3,3)*T(i+1,j+1);
                h5 = H5(1,1)*T(i-1,j-1) + H5(1,2)*T(i-1,j) + H5(1,3)*T(i-1,j+1) + H5(2,1)*T(i,j-1) + H5(2,2)*T(i,j) + H5(2,3)*T(i,j+1) + H5(3,1)*T(i+1,j) + H5(3,2)*T(i+1,j)+H5(3,3)*T(i+1,j+1);
                h6 = H6(1,1)*T(i-1,j-1) + H6(1,2)*T(i-1,j) + H6(1,3)*T(i-1,j+1) + H6(2,1)*T(i,j-1) + H6(2,2)*T(i,j) + H6(2,3)*T(i,j+1) + H6(3,1)*T(i+1,j) + H6(3,2)*T(i+1,j)+H6(3,3)*T(i+1,j+1);
                h7 = H7(1,1)*T(i-1,j-1) + H7(1,2)*T(i-1,j) + H7(1,3)*T(i-1,j+1) + H7(2,1)*T(i,j-1) + H7(2,2)*T(i,j) + H7(2,3)*T(i,j+1) + H7(3,1)*T(i+1,j) + H7(3,2)*T(i+1,j)+H7(3,3)*T(i+1,j+1);
                h8 = H8(1,1)*T(i-1,j-1) + H8(1,2)*T(i-1,j) + H8(1,3)*T(i-1,j+1) + H8(2,1)*T(i,j-1) + H8(2,2)*T(i,j) + H8(2,3)*T(i,j+1) + H8(3,1)*T(i+1,j) + H8(3,2)*T(i+1,j)+H8(3,3)*T(i+1,j+1);
                
                MMax = [abs(h1),abs(h2),abs(h3),abs(h4),abs(h5),abs(h6),abs(h7),abs(h8)];
                 newImage(i,j) = max(MMax);
            end
    end
    set(handles.imageSolved,'HandleVisibility','ON');
    axes(handles.imageSolved);
    imshow(im2uint8(newImage));     
end

set(handles.undoButton,'enable','on');

% --- Executes on selection change in optionSelect.
function optionSelect_Callback(hObject, eventdata, handles)
% hObject    handle to optionSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns optionSelect contents as cell array
%        contents{get(hObject,'Value')} returns selected item from optionSelect


% --- Executes during object creation, after setting all properties.
function optionSelect_CreateFcn(hObject, eventdata, handles)
% hObject    handle to optionSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in operatorSelect.
function operatorSelect_Callback(hObject, eventdata, handles)
% hObject    handle to operatorSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns operatorSelect contents as cell array
%        contents{get(hObject,'Value')} returns selected item from operatorSelect

%Kirsch算子只能取最大
str=get(handles.operatorSelect,'String');
val=get(handles.operatorSelect,'Value');
if strcmp(str(val),'Kirsch算子')
    set(handles.optionSelect,'value',1);
    set(handles.optionSelect,'String',{'取最大'});
end
if strcmp(str(val),'Sobel算子')
    set(handles.optionSelect,'String',{'取最大';'取和'});
end

% --- Executes during object creation, after setting all properties.
function operatorSelect_CreateFcn(hObject, eventdata, handles)
% hObject    handle to operatorSelect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in selectFile.
function selectFile_Callback(hObject, eventdata, handles)
% hObject    handle to selectFile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename,pathname]=uigetfile({'*.*';'*.jpg';'*.bmp';'*.tif'},'载入图像');
if isequal(filename,0)||isequal(pathname,0)
    errordlg('没有选中文件','出错');
    return;
else
    file=[pathname,filename];
    global S%设置一个全局变量S，保存初始图像路径，以便之后的还原操作
    S=file;
    x=imread(file);
    set(handles.imageUnsolved,'HandleVisibility','ON');
    axes(handles.imageUnsolved);
    imshow(x);
    set(handles.imageSolved,'HandleVisibility','OFF');
    axes(handles.imageSolved);
    imshow(x);
    guidata(hObject,handles);
end
set(handles.startButton,'enable','on');
set(handles.saveButton,'enable','on');

% --- Executes on button press in undoButton.
function undoButton_Callback(hObject, eventdata, handles)
% hObject    handle to undoButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global S;   %还原
axes(handles.imageSolved);
y=imread(S);
imshow(y);
guidata(hObject,handles);



% --- Executes on button press in saveButton.
function saveButton_Callback(hObject, eventdata, handles)
% hObject    handle to saveButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

[sfilename,sfilepath]=uiputfile({'*.jpg';'*.bmp';'*.tif';'*.*'},'保存图像文件','untitled.jpg');
if ~isequal([sfilename,sfilepath],[0,0])
    sfilefullname=[sfilepath,sfilename];
    pix=getframe(handles.imageSolved);
    imwrite(pix.cdata,sfilefullname);
else
    msgbox('你按了取消键','保存失败');
end
