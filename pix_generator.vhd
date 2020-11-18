library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity pix_generator is
	Port (
		clk : in STD_LOGIC;
		blank : in STD_LOGIC;
		pix_clk : in STD_LOGIC;
		x_coord : in STD_LOGIC_VECTOR(9 downto 0);
		y_coord : in STD_LOGIC_VECTOR(9 downto 0)
		rgb_in  : in STD_LOGIC_VECTOR(3 downto 0);
		rgb_out : out STD_LOGIC_VECTOR(2 downto 0);
		addr : out STD_LOGIC_VECTOR(13 downto 0);
	);
end pix_generator;

architecture Behavioral of pix_generator is

	constant size_x : integer range 0 to 2**10-1 := 128;
	constant size_y : integer range 0 to 2**10-1 := 128;
	constant BLACK : STD_LOGIC_VECTOR(2 downto 0) := "000";

	signal s_rgb : STD_LOGIC_VECTOR(2 downto 0);
	signal s_video_on : STD_LOGIC;
	signal s_x_coord : unsigned(9 downto 0);
	signal s_y_coord : unsigned(9 downto 0);

	signal s_addr : STD_LOGIC_VECTOR(13 downto 0);
	signal s_enable : STD_LOGIC;
	signal s_vis_area : STD_LOGIC;

	COMPONENT program_counter
	PORT (
		clk : IN std_logic;
		ena : IN std_logic;          
		addr : OUT std_logic_vector(13 downto 0)
	);
	END COMPONENT;
	
begin

	Inst_program_counter: program_counter PORT MAP (
		clk => clk,
		ena => s_enable,
		addr => s_addr
	);
	
	s_video_on <= (blank);
	s_x_coord <= unsigned(x_coord);
	s_y_coord <= unsigned(y_coord);
	addr <= s_addr;
	
	-- signal to increment pixel counter
	s_enable <= '1' when s_vis_area = '1' and pix_clk = '1' else '0';
		
	-- SCREEN CENTER
	-- determines if the scan pointer is inside the visible (memory mapped) region
	-- s_vis_area  <= '0' when s_y_coord >= 304 or s_y_coord <= 175 
	-- or s_x_coord >= 384 or s_x_coord <= 255 else '1';
	s_vis_area <= '1' when (s_y_coord < size_y and s_x_coord < size_x) else '0';

	-- if not visible area output BLACK
	s_rgb <= BLACK when s_vis_area = '0' else rgb_in(2 downto 0);	
	
	-- output black during V,H blanks
	rgb_out <= s_rgb when s_video_on = '1' else BLACK;
	
end Behavioral;
