library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity vga_sync is

	Port (
		clk : in STD_LOGIC;
		pix_clk : out STD_LOGIC; -- 25 MHz
		vsync : out STD_LOGIC;
		hsync : out STD_LOGIC;
		pixel_x : out STD_LOGIC_VECTOR(9 downto 0);
		pixel_y : out STD_LOGIC_VECTOR(9 downto 0);
		video_on : out STD_LOGIC
	);

end vga_sync;

architecture Behavioral of vga_sync is

	constant N_PIXELS : integer := 800;
	constant N_VIS_PIXELS : integer := 640;
	constant R_BORDER : integer := 16;
	constant H_RETRACE : integer := 96;

	constant N_LINES : integer := 521;
	constant N_VIS_LINES : integer := 480;
	constant B_BORDER : integer := 10;
	constant T_BORDER : integer := 29;
	constant V_RETRACE : integer := 2;
	
	signal clk_25mhz : STD_LOGIC := '0';
	signal pixel_counter : unsigned(9 downto 0) := (others => '1');
	signal line_counter : unsigned(9 downto 0) := (others => '0');
	signal s_hsync : STD_LOGIC := 'X';
	signal s_vsync : STD_LOGIC := 'X';
	signal h_video_on : STD_LOGIC := 'X';
	signal v_video_on : STD_LOGIC := 'X';

begin

	gen_clock : process(clk)
	begin
		if rising_edge(clk) then
			clk_25mhz <= not(clk_25mhz);
		end if;
	end process;

	hor_scan : process(clk_25mhz)
	begin 
		if rising_edge(clk_25mhz) then
			if pixel_counter = N_PIXELS-1 then
				pixel_counter <= (others => '0');
							
				-- increase line counter when h_scan is done.
				if line_counter = N_LINES-1 then
					line_counter <= (others => '0');
				else
					line_counter <= line_counter + 1;
				end if;
				
			else
				pixel_counter <= pixel_counter + 1;
			end if;
		end if;
	end process;
			
	h_video_on <= '1' when pixel_counter < (N_VIS_PIXELS) else '0';
	s_hsync <= '0' when (pixel_counter >= N_VIS_PIXELS+R_BORDER and
		pixel_counter < N_VIS_PIXELS+R_BORDER+H_RETRACE) else '1';
	
	v_video_on <= '1' when line_counter < (N_VIS_LINES) else '0';
	s_vsync <= '0' when (line_counter >= N_VIS_LINES+B_BORDER and
		line_counter < N_VIS_LINES+B_BORDER+V_RETRACE) else '1';
	
	--------------------
	-- Port assignment
	--------------------
	pixel_x <= std_logic_vector(pixel_counter);
	pixel_y <= std_logic_vector(line_counter);
	hsync <= s_hsync;
	vsync <= s_vsync;
	video_on <= (h_video_on and v_video_on);
	pix_clk <= clk_25mhz;
	
end Behavioral;
