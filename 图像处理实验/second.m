function varargout = second(varargin)
% SECOND MATLAB code for second.fig
%      SECOND, by itself, creates a new SECOND or raises the existing
%      singleton*.
%
%      H = SECOND returns the handle to a new SECOND or the handle to
%      the existing singleton*.
%
%      SECOND('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SECOND.M with the given input arguments.
%
%      SECOND('Property','Value',...) creates a new SECOND or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before second_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to second_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help second

% Last Modified by GUIDE v2.5 19-Oct-2019 11:14:25

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @second_OpeningFcn, ...
                   'gui_OutputFcn',  @second_OutputFcn, ...
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


% --- Executes just before second is made visible.
function second_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to second (see VARARGIN)

% Choose default command line output for second
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

set(handles.pushbutton2,'enable','off');
set(handles.pushbutton3,'enable','off');
set(handles.pushbutton4,'enable','off');

% UIWAIT makes second wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = second_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename,pathname]=uigetfile({'*.*';'*.jpg';'*.bmp';'*.tif'},'����ͼ��');
if isequal(filename,0)||isequal(pathname,0)
    errordlg('û��ѡ���ļ�','����');
    return;
else
    file=[pathname,filename];
    global S%����һ��ȫ�ֱ���S�������ʼͼ��·�����Ա�֮��Ļ�ԭ����
    S=file;
    x=imread(file);
    set(handles.one,'HandleVisibility','ON');

    axes(handles.one);
    imshow(x);
    set(handles.two,'HandleVisibility','OFF');
    axes(handles.two);
    imshow(x);
    set(handles.three,'HandleVisibility','OFF');
    axes(handles.three);
    imshow(x);
    guidata(hObject,handles);
end
set(handles.pushbutton2,'enable','on');
set(handles.pushbutton4,'enable','on');

% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global S;   %ȫ�ֱ���S�����ų�ʼͼ��        
% ��ȡRGBͼ��  
I = imread(S); 
% ת��Ϊ�Ҷ�ͼ��  
gray = rgb2gray(I);

% ��ͼ��ת��ΪYCbCr��ɫ�ռ�  
Ycbcr = rgb2ycbcr(I);  
% ���ͼ���Ⱥ͸߶�  
[Height Width] = size(gray);   
% ���ݷ�ɫģ�ͽ�ͼ���ֵ�� 
% M = [114.3763 150.1374]';%��ɫ��ֵ
% C = [99.7596 -68.6397;-68.6397 84.49837];%��ɫ����
% for i=1:Height
%     for j=1:Width
% 		x = double([Ycbcr(i,j,2);Ycbcr(i,j,3)]);
%         gray(i,j)=exp(-0.5*(x-M)'*inv(C)*(x-M));%�����ɫ��Ȼ��     
%     end
% end
% 
% %�ҵ�����ɫ��Ȼ��
% Max = max(max(gray));
% for i=1:Height
%     for j=1:Width
% 		if (gray(i,j)/Max)>0.3 %ÿһ���ص�ķ�ɫ��Ȼ�ȳ��������Ȼ����Ϊ�õ����ڷ�ɫ�ĸ���
%             gray(i,j)=255;
%         else
%             gray(i,j)=0;
%         end
%     end
% end

% ��Բģ�� 
for i=1:Height
    for j=1:Width
		%�����������ʵ���ϵ���ο�
 		a = 25.39;  
		b = 14.03;  
		ecx = 1.60;  
		ecy = 2.41;  
		sita = 2.53;  
		cx = 109.38;  
		cy = 152.02;  
		coe = [cos(sita) sin(sita);-sin(sita) cos(sita)];  %ϵ������
		
		Y = Ycbcr(i,j,1);
		Cb = Ycbcr(i,j,2);
		Cr = Ycbcr(i,j,3);
		
		% ������ȴ���230���򽫳�����ͬʱ����Ϊԭ����1.1��  
		if(Y > 230)
			a = 1.1*a;  
			b = 1.1*b;  
		end  
		% ���ݹ�ʽ���м���  
		Cb = double(Cb);  
		Cr = double(Cr);  
		t = [(Cb-cx);(Cr-cy)];  
		temp = coe*t;  
		is_vaild = (temp(1) - ecx)^2/a^2 + (temp(2) - ecy)^2/b^2;  
		% ����1���Ƿ�ɫ������0������Ϊ��ɫ������1  
		if is_vaild> 1  
			gray(i,j)=0;  
		else  
			gray(i,j)=255;
		end	
    end
end 


set(handles.two,'HandleVisibility','ON');
axes(handles.two);

% ��ֵͼ����̬ѧ����  
Block=strel('disk',4); 
% imclose�������ٸ�ʴ
%gray = imclose(gray,Block);
% imopen�ȸ�ʴ������
gray = imopen(gray,Block);
%��ֵ�˲�
%gray = medfilt2(gray,[3,3]);
imshow(gray);
% ȡ��ͼƬ�����а�����ɫ�������С����  
[L,num] = bwlabel(gray,8);
STATS = regionprops(L,'BoundingBox') ; 
% ��ž���ɸѡ�Ժ�õ������о��ο�  
set(handles.three,'HandleVisibility','ON');
axes(handles.three);
imshow(I);
%����ͨ���򻭾���

%�����ж�������ʽ

%�����	0.55~2
%����˲� R=����ɫ���/����ͼ���


for i = 1:num
    pos = STATS(i).BoundingBox; 
	%pos(1) (2) (3) (4) �ֱ��Ӧ��������(x,y),��,��
	
	%�����֮����0.55~2
	rate = pos(4)/pos(3)
	if rate>0.55 && rate<2 && pos(3)*pos(4)>500 && pos(3)>35 && pos(4)>35
		rectangle('position',pos,'edgecolor','r');
	end
end	

set(handles.pushbutton3,'enable','on');

% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global S;   %��ԭ
axes(handles.two);
imshow('');
axes(handles.three);
imshow('');
guidata(hObject,handles);

% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[sfilename,sfilepath]=uiputfile({'*.jpg';'*.bmp';'*.tif';'*.*'},'����ͼ���ļ�','untitled.jpg');
if ~isequal([sfilename,sfilepath],[0,0])
    sfilefullname=[sfilepath,sfilename];
    pix=getframe(handles.three);
    imwrite(pix.cdata,sfilefullname);
else
    msgbox('�㰴��ȡ����','����ʧ��');
end
