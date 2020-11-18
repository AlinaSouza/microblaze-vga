library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity top_mcs is

	Port (
		clk : in  STD_LOGIC;
		tx: out STD_LOGIC;
		rx: in STD_LOGIC;
		reset: in STD_LOGIC;
		lcd_rw : out STD_LOGIC;
		lcd_out : out STD_LOGIC_VECTOR (5 downto 0);
		rgb_out : out  STD_LOGIC_VECTOR (2 downto 0);
		vsync : out  STD_LOGIC;
		hsync : out  STD_LOGIC
	);
	
end top_mcs;

architecture Behavioral of top_mcs is

	COMPONENT microblaze_mcs
	PORT (
		Clk : IN STD_LOGIC;
		Reset : IN STD_LOGIC;
		UART_Rx : IN STD_LOGIC;
		UART_Tx : OUT STD_LOGIC;
		GPO1 : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
		GPO2 : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
		GPI1 : IN STD_LOGIC_VECTOR(7 DOWNTO 0)
	);
	END COMPONENT;

	COMPONENT ram_controller
	PORT (
		clk : IN std_logic;
		p_wr_enaA : IN std_logic;
		p_addrA : IN std_logic_vector(13 downto 0);
		p_data_inA : IN std_logic_vector(3 downto 0);
		p_addrB : IN std_logic_vector(13 downto 0);          
		p_data_outA : OUT std_logic_vector(3 downto 0);
		p_data_outB : OUT std_logic_vector(3 downto 0)
	);
	END COMPONENT;

	COMPONENT pix_generator
	PORT (
		clk : IN std_logic;
		blank : IN std_logic;
		rgb_in : IN std_logic_vector(3 downto 0);
		pix_clk : IN std_logic;
		x_coord : IN std_logic_vector(9 downto 0);
		y_coord : IN std_logic_vector(9 downto 0);          
		rgb_out : OUT std_logic_vector(2 downto 0);
		addr : OUT std_logic_vector(13 downto 0)
	);
	END COMPONENT;

	COMPONENT vga_sync
	PORT (
		clk : IN std_logic;          
		pix_clk : OUT std_logic;
		vsync : OUT std_logic;
		hsync : OUT std_logic;
		pixel_x : OUT std_logic_vector(9 downto 0);
		pixel_y : OUT std_logic_vector(9 downto 0);
		video_on : OUT std_logic
	);
	END COMPONENT;

	signal s_zero_sig : STD_LOGIC;

	-- LCD output
	signal s_lcd_output : STD_LOGIC_VECTOR(7 downto 0);

	-- UART
	signal s_uart_tx : STD_LOGIC;
	signal s_uart_rx : STD_LOGIC;

	-- GPO1
	signal s_gpo1 : STD_LOGIC_VECTOR(31 downto 0);
	
	-- GPI1
	signal s_gpi1 : STD_LOGIC_VECTOR(7 downto 0);

	-- VGA related signals
	signal s_clk_25mhz : STD_LOGIC;
	signal s_video_on : STD_LOGIC;
	signal s_vsync : STD_LOGIC;
	signal s_hsync : STD_LOGIC;
	signal s_portB_addr : STD_LOGIC_VECTOR(13 downto 0);
	signal s_rgb_in	: STD_LOGIC_VECTOR(3 downto 0);
	signal s_rgb_out : STD_LOGIC_VECTOR(2 downto 0);
	signal s_pixel_x : STD_LOGIC_VECTOR(9 downto 0);
	signal s_pixel_y : STD_LOGIC_VECTOR(9 downto 0);
	
begin

	s_zero_sig <= '0';
	s_uart_rx <= rx;	
	lcd_out <= s_lcd_output(5 downto 0);
	lcd_rw <= '0';	
	tx <= s_uart_tx;
	vsync <= s_vsync;
	hsync <= s_hsync;
	rgb_out	<= s_rgb_out;
	
	mcs_0 : microblaze_mcs PORT MAP (
		Clk => clk,
		Reset => s_zero_sig,
		UART_Rx => s_uart_rx,
		UART_Tx => s_uart_tx,
		GPO1 => s_gpo1,
		GPO2 => s_lcd_output,
		GPI1 => s_gpi1
	);

	ram_controller_0: ram_controller PORT MAP (
		clk => clk,
		p_wr_enaA => s_gpo1(18),
		p_addrA => s_gpo1(17 downto 4),
		p_data_outA => s_gpi1(3 downto 0),
		p_data_inA => s_gpo1(3 downto 0),
		p_addrB => s_portB_addr,
		p_data_outB => s_rgb_in
	);

	pix_generator_0: pix_generator PORT MAP (
		clk => clk,
		blank => s_video_on,
		rgb_out => s_rgb_out,
		rgb_in => s_rgb_in,
		addr => s_portB_addr,
		pix_clk => s_clk_25mhz,
		x_coord => s_pixel_x,
		y_coord => s_pixel_y
	);

	vga_sync_0: vga_sync PORT MAP (
		clk => clk,
		pix_clk => s_clk_25mhz,
		vsync => s_vsync,
		hsync => s_hsync,
		pixel_x => s_pixel_x,
		pixel_y => s_pixel_y,
		video_on => s_video_on
	);

end Behavioral;
